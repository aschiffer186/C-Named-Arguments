#ifndef NAMED_ARGUMENTS_HPP
#define NAMED_ARGUMENTS_HPP

#include <type_traits>
#include <utility>

template<typename ArgumentType, typename Tag> 
struct NamedArgument 
{
public:
    using TagType = Tag;

    template<typename U> 
    explicit constexpr NamedArgument(U&& arg)
    : arg_(std::forward<U>(arg))
    {

    }

    constexpr operator auto&&() const 
    {
        if constexpr (std::is_rvalue_reference_v<ArgumentType>)
            return std::move(arg_);
        return arg_;
    }
private:
    ArgumentType arg_;
};

template<typename ArgumentType, typename Tag> 
struct UserArgument
{
    template<typename U>
    constexpr NamedArgument<ArgumentType, Tag> operator=(U&& arg) const 
    {
        return {std::forward<U>(arg)};
    }
};

namespace Detail
{
    template<typename>
    struct is_named_argument : std::false_type {};

    template<typename T, typename U> 
    struct is_named_argument<NamedArgument<T, U>> : std::true_type {};

    template<bool SeenNamedArgument, typename Tp, typename... Tps> 
    struct is_well_formatted_impl : 
        std::bool_constant<(SeenNamedArgument) ? is_named_argument<Tp>::value
            && is_well_formatted_impl<true, Tps...>::value
        : is_well_formatted_impl<is_named_argument<Tp>::value, Tps...>::value>
    {

    };

    template<bool SeenNamedArgument, typename Tp> 
    struct is_well_formatted_impl<SeenNamedArgument, Tp> : std::true_type {};
}
/**
 * @brief Checks to see if an argument list containing positional and named arguments is well formatted
 * 
 * This class template provides a static member variable that is "true" if a list of arguments is 
 * well formatted and false otherwise. A list of arguments is well formatted if there are no positional 
 * arguments following named arguments.
 *
 * @tparam SeenNamedArgument 
 * @tparam Tp 
 * @tparam Tps 
 */
template<typename Tp, typename... Tps> 
struct is_well_formatted : Detail::is_well_formatted_impl<false, Tp, Tps...> {};

template<typename... Tps>
inline constexpr bool is_well_formatted_v = is_well_formatted<Tps...>::value;

#define MAKE_NAMED_ARGUMENT(type, name)\
struct name##Tag_;\
inline constexpr UserArgument<type, name##Tag_> name;

#endif
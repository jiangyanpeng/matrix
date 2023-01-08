#ifndef __PPM_MATRIX_OPERATOR_H__
#define __PPM_MATRIX_OPERATOR_H__

#include "Type.hpp"

namespace ppm
{
    // operators
    struct plus_t
    {
        constexpr explicit plus_t() = default;

        template <typename LT, typename RT>
        auto operator()(const LT &lhs, const RT &rhs) -> decltype(lhs + rhs) const
        {
            return lhs + rhs;
        }
    };
    constexpr plus_t plus{};

    struct minus_t
    {
        constexpr explicit minus_t() = default;

        template <typename LT, typename RT>
        auto operator()(const LT &lhs, const RT &rhs) -> decltype(lhs - rhs) const
        {
            return lhs - rhs;
        }
    };
    constexpr minus_t minus{};

    struct multiply_t
    {
        constexpr explicit multiply_t() = default;

        template <typename LT, typename RT>
        auto operator()(const LT &lhs, const RT &rhs) -> decltype(lhs * rhs) const
        {
            return lhs * rhs;
        }
    };
    constexpr multiply_t mul{};

    struct divide_t
    {
        constexpr explicit divide_t() = default;

        template <typename LT, typename RT>
        auto operator()(const LT &lhs, const RT &rhs) -> decltype(lhs / rhs) const
        {
            return lhs / rhs;
        }
    };
    constexpr divide_t div{};

    // template <typename T>
    // struct expr_scalar
    // {
    // private:
    //     const T &s;

    // public:
    //     constexpr expr_scalar(const T &v)
    //         : s(v)
    //     {
    //     }
    //     constexpr T const &operator[](std::size_t) const
    //     {
    //         return s;
    //     }
    //     constexpr std::size_t size() const
    //     {
    //         return 0;
    //     }
    // };

    // template <typename T>
    // struct expr_traits
    // {
    //     using ExprRef = T const &;
    // };

    // template <typename T>
    // struct expr_traits<expr_scalar<T>>
    // {
    //     using ExprRef = expr_scalar<T>;
    // };

    // template <typename T>
    // class expr
    // {
    // public:
    //     using expr_type = expr<T>;
    //     const T &self() const { return static_cast<const T &>(*this); }
    //     T &self() { return static_cast<T &>(*this); }

    // protected:
    //     explicit expr() = default;
    //     constexpr size_t size() { return self().size_impl(); }
    //     expr_type operator[](size_t idx) const { return self().at_impl(idx); }
    //     expr_type operator()() const { return self()(); }
    // };

    // template <typename T>
    // class expr_result : expr<expr_result<T>>
    // {
    // public:
    //     using base_type = expr<expr_result<T>>;
    //     using base_type::size;
    //     using base_type::operator[];
    //     friend base_type;

    //     explicit expr_result(const T &val) : value(val) {}
    //     size_t size_impl() const { return value.size(); }
    //     base_type at_impl(size_t idx) const { return value[idx]; }
    //     base_type operator()() const { return (value); }

    // private:
    //     typename expr_traits<T>::ExprRef value;
    // };

    // template <typename Ops, typename lExpr, typename rExpr>
    // class biops : public expr<biops<Ops, lExpr, rExpr>>
    // {
    // public:
    //     using base_type = expr<biops<Ops, lExpr, rExpr>>;
    //     using base_type::size;
    //     using base_type::operator[];
    //     friend base_type;

    //     explicit biops(const Ops &ops, const lExpr &lxpr, const rExpr &rxpr)
    //         : m_ops(ops), m_lxpr(lxpr), m_rxpr(rxpr) {}

    //     constexpr size_t size_impl() { return More(m_lxpr.size(), m_rxpr.size()); }

    //     // auto at_impl(size_t idx) -> decltype(Ops(lExpr[idx], rExpr[idx])) const { return m_ops(m_lxpr[idx], m_rxpr[idx]); }

    //     template <typename T>
    //     operator T()
    //     {
    //         T res{};
    //         for (size_t idx = 0; idx < res.size(); ++idx)
    //         {
    //             res[idx] = (*this)[idx];
    //         }
    //         return res;
    //     }
    //     template <typename T, disable_arithmetic_type_t<T> * = nullptr, typename T::expr_type>
    //     auto operator+(const T &rhs)
    //     {
    //         return biops<expr_plus_t, biops<Ops, lExpr, rExpr>, T>(expr_plus, *this, rhs);
    //     }
    //     template <typename T, disable_arithmetic_type_t<T> * = nullptr>
    //     auto operator+(const T &rhs)
    //     {
    //         using result_t = expr_result<T>;
    //         return biops<expr_plus_t, biops<Ops, lExpr, rExpr>, result_t>(expr_plus, *this, result_t(rhs));
    //     }
    //     template <typename T, enable_arith_type_t<T> * = nullptr>
    //     auto operator+(const T &rhs)
    //     {
    //         using result_s = expr_result<expr_scalar<T>>;
    //         return biops<expr_plus_t, biops<Ops, lExpr, rExpr>, result_s>(expr_plus, *this, result_s(rhs));
    //     }
    //     template <typename T, disable_arithmetic_type_t<T> * = nullptr, typename T::expr_type>
    //     auto operator-(const T &rhs)
    //     {
    //         return biops<expr_minus_t, biops<Ops, lExpr, rExpr>, T>(expr_minus, *this, rhs);
    //     }
    //     template <typename T, disable_arithmetic_type_t<T> * = nullptr>
    //     auto operator-(const T &rhs)
    //     {
    //         using result_t = expr_result<T>;
    //         return biops<expr_minus_t, biops<Ops, lExpr, rExpr>, result_t>(expr_minus, *this, result_t(rhs));
    //     }
    //     template <typename T, enable_arith_type_t<T> * = nullptr>
    //     auto operator-(const T &rhs)
    //     {
    //         using result_s = expr_result<expr_scalar<T>>;
    //         return biops<expr_minus_t, biops<Ops, lExpr, rExpr>, result_s>(expr_minus, *this, result_s(rhs));
    //     }
    //     template <typename T, enable_arith_type_t<T> * = nullptr>
    //     auto operator*(const T &rhs)
    //     {
    //         using result_s = expr_result<expr_scalar<T>>;
    //         return biops<expr_mul_t, biops<Ops, lExpr, rExpr>, result_s>(expr_mul, *this, result_s(rhs));
    //     }
    //     template <typename T, enable_arith_type_t<T> * = nullptr>
    //     auto operator/(const T &rhs)
    //     {
    //         using result_s = expr_result<expr_scalar<T>>;
    //         return biops<expr_div_t, biops<Ops, lExpr, rExpr>, result_s>(expr_div, *this, result_s(rhs));
    //     }

    // private:
    //     Ops m_ops;
    //     lExpr m_lxpr;
    //     rExpr m_rxpr;
    // };
}
#endif // __PPM_MATRIX_OPERATOR_H__
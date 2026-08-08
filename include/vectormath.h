#ifndef INCLUDE_VECTOR_MATH_H_
#define INCLUDE_VECTOR_MATH_H_

#include <cmath>
#include <cstddef>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

#include "common.h"

template <size_t N>
struct TupleData;

template <>
struct TupleData<2> {
  Float x{}, y{};

  template <size_t I>
  constexpr const Float& get() const noexcept {
    static_assert(I < 2, "index out of range");
    if constexpr (I == 0)
      return x;
    else
      return y;
  }

  template <size_t I>
  Float& get() noexcept {
    static_assert(I < 2, "index out of range");
    if constexpr (I == 0)
      return x;
    else
      return y;
  }
};

template <>
struct TupleData<3> {
  Float x{}, y{}, z{};

  template <size_t I>
  constexpr const Float& get() const noexcept {
    static_assert(I < 3, "index out of range");
    if constexpr (I == 0)
      return x;
    else if constexpr (I == 1)
      return y;
    else
      return z;
  }

  template <size_t I>
  constexpr Float& get() noexcept {
    static_assert(I < 3, "index out of range");
    if constexpr (I == 0)
      return x;
    else if constexpr (I == 1)
      return y;
    else
      return z;
  }
};

template <>
struct TupleData<4> {
  Float x{}, y{}, z{}, w{};

  template <size_t I>
  constexpr const Float& get() const noexcept {
    static_assert(I < 4, "index out of range");
    if constexpr (I == 0)
      return x;
    else if constexpr (I == 1)
      return y;
    else if constexpr (I == 2)
      return z;
    else
      return w;
  }

  template <size_t I>
  constexpr Float& get() noexcept {
    static_assert(I < 4, "index out of range");
    if constexpr (I == 0)
      return x;
    else if constexpr (I == 1)
      return y;
    else if constexpr (I == 2)
      return z;
    else
      return w;
  }
};

template <size_t N, typename Tag, template <typename> class... Skills>
  requires(N > 1 and N < 5)
class Tuple : public TupleData<N>, public Skills<Tuple<N, Tag, Skills...>>... {
 public:
  static constexpr size_t Dim = N;

  Tuple() = default;

  template <typename... Args>
    requires(sizeof...(Args) == N and
             (std::is_convertible_v<Args, Float> and ...))
  explicit Tuple(Args... args) : TupleData<N>(static_cast<Float>(args)...) {}

  Tuple(const Tuple&) = default;
  Tuple& operator=(const Tuple&) = default;
  Tuple(Tuple&&) = default;
  Tuple& operator=(Tuple&&) = default;
  ~Tuple() = default;

  constexpr size_t dimension() const { return N; }
};

/* CRTP Skills */
template <typename Derived>
class Addable {
  friend Derived& operator+=(Derived& lhs, const Derived& rhs) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((lhs.template get<I>() += rhs.template get<I>()), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return lhs;
  }

  friend Derived operator+(Derived lhs, const Derived& rhs) {
    lhs += rhs;
    return lhs;
  }
};

template <typename Derived>
class Subtractable {
  friend Derived& operator-=(Derived& lhs, const Derived& rhs) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((lhs.template get<I>() -= rhs.template get<I>()), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return lhs;
  }

  friend Derived operator-(Derived lhs, const Derived& rhs) {
    lhs -= rhs;
    return lhs;
  }
};

template <typename Derived>
class Negatable {
  friend Derived operator-(Derived val) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((val.template get<I>() = -val.template get<I>()), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return val;
  }
};

template <typename Derived>
class Multipliable {
  friend Derived& operator*=(Derived& lhs, const Float& k) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((lhs.template get<I>() *= k), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return lhs;
  }

  friend Derived operator*(Derived lhs, const Float k) {
    lhs *= k;
    return lhs;
  }

  friend Derived operator*(const Float k, const Derived& lhs) {
    return lhs * k;
  }
};

template <typename Derived>
class Dividable {
  friend Derived& operator/=(Derived& lhs, const Float& k) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((lhs.template get<I>() /= k), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return lhs;
  }

  friend Derived operator/(Derived lhs, const Float k) {
    lhs /= k;
    return lhs;
  }
};

template <typename Derived>
class HasL2Distance {
  friend Float length_squared(const Derived& d) { return dot(d, d); }

  friend Float length(const Derived& d) { return std::sqrt(length_squared(d)); }

  friend Derived normalize(const Derived& v) {
    const Float length_v{length(v)};
    if (length_v < std::numeric_limits<Float>::epsilon())
      throw std::runtime_error("input vector has a length very close to 0.");
    return v / length_v;
  }

  friend bool near_zero(const Derived& v) {
    return [&]<size_t... I>(std::index_sequence<I...>) {
      return ((std::abs(v.template get<I>()) < VERY_SMALL) and ...);
    }(std::make_index_sequence<Derived::Dim>{});
  }
};

/* Element-wise product (mainly for colors)*/
template <typename Derived>
class HadamardProductable {
  friend Derived hadamard_product(const Derived& c1, const Derived& c2,
                                  const size_t max_val = 255) {
    Derived c3;
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((c3.template get<I>() = c1.template get<I>() * c2.template get<I>() /
                               static_cast<Float>(max_val)),
       ...);
    }(std::make_index_sequence<Derived::Dim>{});
    return c3;
  }
};

template <typename Derived>
class Printable {
  friend std::ostream& operator<<(std::ostream& o, const Derived& d) {
    // up until (including) one before last element, so we have the space
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((o << d.template get<I>() << " "), ...);
    }(std::make_index_sequence<Derived::Dim - 1>{});
    // for the last element to prevent space at the end
    o << d.template get<Derived::Dim - 1>();
    return o;
  }
};

template <typename Derived>
class DotProductable {
  friend Float dot(const Derived& u, const Derived& v) {
    return [&]<size_t... I>(std::index_sequence<I...>) {
      return ((u.template get<I>() * v.template get<I>()) + ...);
    }(std::make_index_sequence<Derived::Dim>{});
  }
};

template <typename Derived>
class CrossProductable {
  friend Derived cross(const Derived& u, const Derived& v) {
    static_assert(Derived::Dim == 3,
                  "Cross product is only defined for 3D vectors.");
    return Derived(u.y * v.z - u.z * v.y, -u.x * v.z + u.z * v.x,
                   u.x * v.y - u.y * v.x);
  }
};

template <typename Derived>
// TODO name better!
class ReflectRefractable {
  friend Derived reflect(const Derived& v, const Derived& normal) {
    return v - 2 * dot(v, normal) * normal;
  }

  friend Derived refract(const Derived& uv, const Derived& n,
                         Float etai_over_etat) {
    auto cos_theta = std::min(dot(-uv, n), Float(1));
    Derived r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Derived r_out_parallel =
        -std::sqrt(std::abs(1.0 - length_squared(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
  }
};
// Trait to safely extract the dimension of a Tuple even if incomplete
template <typename T>
struct DimensionOf;

template <size_t N, typename Tag, template <typename> class... Skills>
struct DimensionOf<Tuple<N, Tag, Skills...>> {
  static constexpr size_t value = N;
};

template <typename Derived>
class Translateable {
  template <typename Vec>
  // Using DimensionOf and similarly for the next operators, to solve
  // "incomplete type '‘Tuple...::Skill>’' used in nested name specifier" error
  // (with gcc)
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived& operator+=(Derived& p, const Vec& v) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((p.template get<I>() += v.template get<I>()), ...);
    }(std::make_index_sequence<Derived::Dim>{});
    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator+(Derived p, const Vec& v) {
    p += v;
    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator+(const Vec& v, Derived p) {
    p += v;
    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived& operator-=(Derived& p, const Vec& v) {
    [&]<size_t... I>(std::index_sequence<I...>) {
      ((p.template get<I>() -= v.template get<I>()), ...);
    }(std::make_index_sequence<Derived::Dim>{});

    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator-(Derived p, const Vec& v) {
    p -= v;
    return p;
  }
};

template <typename VectorType>
struct PointDifferenceable {
  template <typename Derived>
  class Skill {
    friend VectorType operator-(const Derived& lhs, const Derived& rhs) {
      if constexpr (Derived::Dim == 2)
        return VectorType(lhs.x - rhs.x, lhs.y - rhs.y);
      if constexpr (Derived::Dim == 3)
        return VectorType(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
      if constexpr (Derived::Dim == 4)
        return VectorType(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z,
                          lhs.w - rhs.w);
    }
  };
};

using Vec2 = Tuple<2, struct VectorTag, Addable, Subtractable, Multipliable,
                   Dividable, Negatable, Printable, HasL2Distance,
                   DotProductable, ReflectRefractable>;
using Vec3 = Tuple<3, struct VectorTag, Addable, Subtractable, Multipliable,
                   Dividable, Negatable, Printable, HasL2Distance,
                   DotProductable, CrossProductable, ReflectRefractable>;
using Vec4 = Tuple<4, struct VectorTag, Addable, Subtractable, Multipliable,
                   Dividable, Negatable, Printable, HasL2Distance,
                   DotProductable, ReflectRefractable>;

using Point2 = Tuple<2, struct PointTag, Negatable, Printable, Translateable,
                     PointDifferenceable<Vec2>::Skill>;
using Point3 = Tuple<3, struct PointTag, Negatable, Printable, Translateable,
                     PointDifferenceable<Vec3>::Skill>;
using Point4 = Tuple<4, struct PointTag, Negatable, Printable, Translateable,
                     PointDifferenceable<Vec4>::Skill>;

using Color = Tuple<3, struct ColorTag, Printable, Addable, Multipliable,
                    Dividable, HadamardProductable>;
using Color4 = Tuple<4, struct ColorTag, Printable, Addable, Multipliable,
                     Dividable, HadamardProductable>;

#endif  // INCLUDE_VECTOR_MATH_H_

#ifndef INCLUDE_VECTOR_MATH_H_
#define INCLUDE_VECTOR_MATH_H_

#include <cmath>
#include <cstddef>
#include <limits>
#include <ostream>
#include <stdexcept>

#include "common.h"

template <size_t N>
struct TupleData;

template <>
struct TupleData<2> {
  Float x{}, y{};
  constexpr const Float &operator[](const size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    throw std::logic_error("invalid index");
  }
  Float &operator[](const size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    throw std::logic_error("invalid index");
  }
};

template <>
struct TupleData<3> {
  Float x{}, y{}, z{};
  constexpr const Float &operator[](const size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    throw std::logic_error("invalid index");
  }
  Float &operator[](const size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    throw std::logic_error("invalid index");
  }
};

template <>
struct TupleData<4> {
  Float x{}, y{}, z{}, w{};
  constexpr const Float &operator[](const size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    throw std::logic_error("invalid index");
  }
  Float &operator[](const size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    throw std::logic_error("invalid index");
  }
};

template <size_t N, typename Tag, template <typename> class... Skills>
  requires(N > 1 and N < 5)
class Tuple : public TupleData<N>, public Skills<Tuple<N, Tag, Skills...>>... {
 public:
  static constexpr size_t Dim = N;

  Tuple() {}
  template <typename... Args>
    requires(sizeof...(Args) == N and
             (std::is_convertible_v<Args, Float> and ...))
  explicit Tuple(Args... args) : TupleData<N>(static_cast<Float>(args)...) {}

  Tuple(const Tuple &) = default;
  Tuple &operator=(const Tuple &) = default;
  Tuple(Tuple &&) = default;
  Tuple &operator=(Tuple &&) = default;
  ~Tuple() = default;

  constexpr size_t dimension() const { return N; }
};

/* CRTP Skills */
template <typename Derived>
class Addable {
  friend Derived &operator+=(Derived &lhs, const Derived &rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    if constexpr (Derived::Dim == 3) lhs.z += rhs.z;
    if constexpr (Derived::Dim == 4) {
      lhs.z += rhs.z;
      lhs.w += rhs.w;
    }

    return lhs;
  }

  friend Derived operator+(Derived lhs, const Derived &rhs) {
    lhs += rhs;
    return lhs;
  }
};

template <typename Derived>
class Deductable {
  friend Derived &operator-=(Derived &lhs, const Derived &rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    if constexpr (Derived::Dim == 3) lhs.z -= rhs.z;
    if constexpr (Derived::Dim == 4) {
      lhs.z -= rhs.z;
      lhs.w -= rhs.w;
    }

    return lhs;
  }

  friend Derived operator-(Derived lhs, const Derived &rhs) {
    lhs -= rhs;
    return lhs;
  }
};

template <typename Derived>
class Negateable {
  friend Derived operator-(Derived val) {
    val.x = -val.x;
    val.y = -val.y;
    if constexpr (Derived::Dim == 3) val.z = -val.z;
    if constexpr (Derived::Dim == 4) {
      val.w = -val.w;
      val.z = -val.z;
    }

    return val;
  }
};

template <typename Derived>
class Multipliable {
  friend Derived &operator*=(Derived &lhs, const Float &k) {
    lhs.x *= k;
    lhs.y *= k;
    if constexpr (Derived::Dim == 3) lhs.z *= k;
    if constexpr (Derived::Dim == 4) {
      lhs.z *= k;
      lhs.w *= k;
    }

    return lhs;
  }

  friend Derived operator*(Derived lhs, const Float &k) {
    lhs *= k;
    return lhs;
  }

  friend Derived operator*(const Float &k, const Derived &lhs) {
    return lhs * k;
  }
};

template <typename Derived>
class Divideable {
  friend Derived &operator/=(Derived &lhs, const Float &k) {
    lhs.x /= k;
    lhs.y /= k;
    if constexpr (Derived::Dim == 3) lhs.z /= k;
    if constexpr (Derived::Dim == 4) {
      lhs.z /= k;
      lhs.w /= k;
    }

    return lhs;
  }

  friend Derived operator/(Derived lhs, const Float &k) {
    lhs /= k;
    return lhs;
  }
};

template <typename Derived>
class HasL2Distance {
  friend Float length_squared(const Derived &d) {
    Float result = d.x * d.x + d.y * d.y;
    if constexpr (Derived::Dim == 3) result += d.z * d.z;
    if constexpr (Derived::Dim == 4) result += d.z * d.z + d.w * d.w;
    return result;
  }

  friend Float length(const Derived &d) {
    if constexpr (std::is_same_v<Float, float>)
      return std::sqrtf(length_squared(d));

    return std::sqrt(length_squared(d));
  }

  friend Derived normalize(const Derived &v) {
    if (length(v) < std::numeric_limits<Float>::epsilon())
      throw std::runtime_error("input vector has a length very close to 0.");
    return v / length(v);
  }

  friend bool near_zero(const Derived &v) {
    bool result = std::abs(v.x) < VERY_SMALL and std::abs(v.y) < VERY_SMALL;
    if constexpr (Derived::Dim == 3) result &= std::abs(v.z) < VERY_SMALL;
    if constexpr (Derived::Dim == 4)
      result &= (std::abs(v.z) < VERY_SMALL and std::abs(v.w) < VERY_SMALL);

    return result;
  }
};

/* Element-wise product (mainly for colors)*/
template <typename Derived>
class HadamardProductable {
  friend Derived hadamard_product(const Derived &c1, const Derived c2,
                                  const size_t max_val = 255) {
    Derived c3;
    c3.x = c1.x * c2.x / static_cast<Float>(max_val);
    c3.y = c1.y * c2.y / static_cast<Float>(max_val);
    if constexpr (Derived::Dim == 3)
      c3.z = c1.z * c2.z / static_cast<Float>(max_val);
    if constexpr (Derived::Dim == 4) {
      c3.z = c1.z * c2.z / static_cast<Float>(max_val);
      c3.w = c1.w * c2.w / static_cast<Float>(max_val);
    }
    return c3;
  }
};

template <typename Derived>
class Printable {
  friend std::ostream &operator<<(std::ostream &o, const Derived &d) {
    o << d.x << " " << d.y;
    if constexpr (Derived::Dim == 3) o << " " << d.z;
    if constexpr (Derived::Dim == 4) o << " " << d.z << " " << d.w;
    return o;
  }
};

template <typename Derived>
class DotProductable {
  friend Float dot(const Derived &u, const Derived &v) {
    Float result = u.x * v.x + u.y * v.y;
    if constexpr (Derived::Dim == 3) result += u.z * v.z;
    if constexpr (Derived::Dim == 4) result += (u.z * v.z + u.w * v.w);
    return result;
  }
};

template <typename Derived>
class CrossProductable {
  friend Derived cross(const Derived &u, const Derived &v) {
    static_assert(Derived::Dim == 3,
                  "Cross product is only defined for 3D vectors.");
    return Derived(u.y * v.z - u.z * v.y, -u.x * v.z + u.z * v.x,
                   u.x * v.y - u.y * v.x);
  }
};

template <typename Derived>
// TODO name better!
class ReflectRefractable {
  friend Derived reflect(const Derived &v, const Derived normal) {
    return v - dot(v, normal) * normal;
  }

  friend Derived refract(const Derived &uv, const Derived &n,
                         Float etai_over_etat) {
    auto cos_theta = std::min(dot(-uv, n), 1.0);
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
  friend Derived &operator+=(Derived &p, const Vec &v) {
    p.x += v.x;
    p.y += v.y;
    if constexpr (Derived::Dim == 3) p.z += v.z;
    if constexpr (Derived::Dim == 4) {
      p.z += v.z;
      p.w += v.w;
    }

    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator+(Derived p, const Vec &v) {
    p += v;
    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator+(const Vec &v, Derived p) {
    p += v;
    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived &operator-=(Derived &p, const Vec &v) {
    p.x -= v.x;
    p.y -= v.y;
    if constexpr (Derived::Dim == 3) p.z -= v.z;
    if constexpr (Derived::Dim == 4) {
      p.z -= v.z;
      p.w -= v.w;
    }

    return p;
  }

  template <typename Vec>
    requires(DimensionOf<Derived>::value == DimensionOf<Vec>::value and
             !std::is_same_v<Derived, Vec>)
  friend Derived operator-(Derived p, const Vec &v) {
    p -= v;
    return p;
  }
};

template <typename VectorType>
struct PointDifferenceable {
  template <typename Derived>
  class Skill {
    friend VectorType operator-(const Derived &lhs, const Derived &rhs) {
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

using Vec2 = Tuple<2, struct VectorTag, Addable, Deductable, Multipliable,
                   Divideable, Negateable, Printable, HasL2Distance,
                   DotProductable, ReflectRefractable>;
using Vec3 = Tuple<3, struct VectorTag, Addable, Deductable, Multipliable,
                   Divideable, Negateable, Printable, HasL2Distance,
                   DotProductable, CrossProductable, ReflectRefractable>;
using Vec4 = Tuple<4, struct VectorTag, Addable, Deductable, Multipliable,
                   Divideable, Negateable, Printable, HasL2Distance,
                   DotProductable, ReflectRefractable>;

using Point2 = Tuple<2, struct PointTag, Negateable, Printable, Translateable,
                     PointDifferenceable<Vec2>::Skill>;
using Point3 = Tuple<3, struct PointTag, Negateable, Printable, Translateable,
                     PointDifferenceable<Vec3>::Skill>;
using Point4 = Tuple<4, struct PointTag, Negateable, Printable, Translateable,
                     PointDifferenceable<Vec4>::Skill>;

using Color = Tuple<3, struct ColorTag, Printable, Addable, Multipliable,
                    Divideable, HadamardProductable>;
using Color4 = Tuple<4, struct ColorTag, Printable, Addable, Multipliable,
                     Divideable, HadamardProductable>;

#endif  // INCLUDE_VECTOR_MATH_H_

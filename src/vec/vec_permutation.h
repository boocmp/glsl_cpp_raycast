#pragma once

#include "vec_details.h"

namespace glsl {

#define _PERMUTATION_OPERATOR_FAST(op)                             \
  template <typename V1, typename T1, size_t... P1>                \
    requires(sizeof...(P1) == sizeof...(P))                        \
  void operator op(const permutation<V1, T1, P1...>& o) noexcept { \
    T tmp[size];                                                   \
    for (size_t i = 0; i < size; ++i)                              \
      (tmp)[i] = (o)[i];                                           \
    for (size_t i = 0; i < size; ++i)                              \
      (*this)[i] op tmp[i];                                        \
  }

#define _PERMUTATION_OPERATOR_SCALAR_FAST(op) \
  void operator op(T scalar) noexcept {       \
    for (size_t i = 0; i < size; ++i)         \
      (*this)[i] op(scalar);                  \
  }

template <class V, typename T, size_t... P>
struct permutation {
  using data_type = T;
  static constexpr const size_t size = sizeof...(P);

  permutation() noexcept = default;

  template <typename V1, typename T1, size_t... P1>
    requires(sizeof...(P1) == sizeof...(P))
  permutation(const permutation<V1, T1, P1...>& o) noexcept {
    if (this != &o) {
      *this = o;
    }
  }

  template <typename V1, typename T1, size_t... P1>
    requires(sizeof...(P1) == sizeof...(P))
  permutation& operator=(const permutation<V1, T1, P1...>& o) noexcept {
    details::copy_permutaion(o, *this);
    return *this;
  }

  T& operator[](size_t index) {
    const size_t decoder[size] = {P...};
    V* storage = reinterpret_cast<V*>(this);
    return storage->data[decoder[index]];
  }

  const T& operator[](size_t index) const {
    const size_t decoder[size] = {P...};
    const V* storage = reinterpret_cast<const V*>(this);
    return reinterpret_cast<const V*>(this)->data[decoder[index]];
  }

  _PERMUTATION_OPERATOR_FAST(+=)
  _PERMUTATION_OPERATOR_FAST(-=)
  _PERMUTATION_OPERATOR_FAST(*=)
  _PERMUTATION_OPERATOR_FAST(/=)

  _PERMUTATION_OPERATOR_SCALAR_FAST(+=)
  _PERMUTATION_OPERATOR_SCALAR_FAST(-=)
  _PERMUTATION_OPERATOR_SCALAR_FAST(*=)
  _PERMUTATION_OPERATOR_SCALAR_FAST(/=)
};

namespace details {

template <class V, typename T, size_t N, size_t... I>
  requires(sizeof...(I) == N)
auto permutation_deductor(std::index_sequence<I...>) -> permutation<V, T, I...>;
}

template <class V, typename T, size_t N>
using permutation_n = decltype(details::permutation_deductor<V, T, N>(
    std::make_index_sequence<N>{}));

#undef _PERMUTATION_OPERATOR_FAST
#undef _PERMUTATION_OPERATOR_SCALAR_FAST

#define ALL_V1_PERMUTATIONS(V, T)           \
  permutation<V, T, 0, 0> xx, rr, ss;       \
  permutation<V, T, 0, 0, 0> xxx, rrr, sss; \
  permutation<V, T, 0, 0, 0, 0> xxxx, rrrr, ssss;

#define ALL_V2_PERMUTATIONS(V, T)                 \
  permutation<V, T, 0, 0> xx, rr, ss;             \
  permutation<V, T, 1, 0> yx, gr, ts;             \
  permutation<V, T, 0, 1> xy, rg, st;             \
  permutation<V, T, 1, 1> yy, gg, tt;             \
  permutation<V, T, 0, 0, 0> xxx, rrr, sss;       \
  permutation<V, T, 1, 0, 0> yxx, grr, tss;       \
  permutation<V, T, 0, 1, 0> xyx, rgr, sts;       \
  permutation<V, T, 1, 1, 0> yyx, ggr, tts;       \
  permutation<V, T, 0, 0, 1> xxy, rrg, sst;       \
  permutation<V, T, 1, 0, 1> yxy, grg, tst;       \
  permutation<V, T, 0, 1, 1> xyy, rgg, stt;       \
  permutation<V, T, 1, 1, 1> yyy, ggg, ttt;       \
  permutation<V, T, 0, 0, 0, 0> xxxx, rrrr, ssss; \
  permutation<V, T, 1, 0, 0, 0> yxxx, grrr, tsss; \
  permutation<V, T, 0, 1, 0, 0> xyxx, rgrr, stss; \
  permutation<V, T, 1, 1, 0, 0> yyxx, ggrr, ttss; \
  permutation<V, T, 0, 0, 1, 0> xxyx, rrgr, ssts; \
  permutation<V, T, 1, 0, 1, 0> yxyx, grgr, tsts; \
  permutation<V, T, 0, 1, 1, 0> xyyx, rggr, stts; \
  permutation<V, T, 1, 1, 1, 0> yyyx, gggr, ttts; \
  permutation<V, T, 0, 0, 0, 1> xxxy, rrrg, ssst; \
  permutation<V, T, 1, 0, 0, 1> yxxy, grrg, tsst; \
  permutation<V, T, 0, 1, 0, 1> xyxy, rgrg, stst; \
  permutation<V, T, 1, 1, 0, 1> yyxy, ggrg, ttst; \
  permutation<V, T, 0, 0, 1, 1> xxyy, rrgg, sstt; \
  permutation<V, T, 1, 0, 1, 1> yxyy, grgg, tstt; \
  permutation<V, T, 0, 1, 1, 1> xyyy, rggg, sttt; \
  permutation<V, T, 1, 1, 1, 1> yyyy, gggg, tttt;

#define ALL_V3_PERMUTATIONS(V, T)                 \
  permutation<V, T, 0, 0> xx, rr, ss;             \
  permutation<V, T, 1, 0> yx, gr, ts;             \
  permutation<V, T, 2, 0> zx, br, ps;             \
  permutation<V, T, 0, 1> xy, rg, st;             \
  permutation<V, T, 1, 1> yy, gg, tt;             \
  permutation<V, T, 2, 1> zy, bg, pt;             \
  permutation<V, T, 0, 2> xz, rb, sp;             \
  permutation<V, T, 1, 2> yz, gb, tp;             \
  permutation<V, T, 2, 2> zz, bb, pp;             \
  permutation<V, T, 0, 0, 0> xxx, rrr, sss;       \
  permutation<V, T, 1, 0, 0> yxx, grr, tss;       \
  permutation<V, T, 2, 0, 0> zxx, brr, pss;       \
  permutation<V, T, 0, 1, 0> xyx, rgr, sts;       \
  permutation<V, T, 1, 1, 0> yyx, ggr, tts;       \
  permutation<V, T, 2, 1, 0> zyx, bgr, pts;       \
  permutation<V, T, 0, 2, 0> xzx, rbr, sps;       \
  permutation<V, T, 1, 2, 0> yzx, gbr, tps;       \
  permutation<V, T, 2, 2, 0> zzx, bbr, pps;       \
  permutation<V, T, 0, 0, 1> xxy, rrg, sst;       \
  permutation<V, T, 1, 0, 1> yxy, grg, tst;       \
  permutation<V, T, 2, 0, 1> zxy, brg, pst;       \
  permutation<V, T, 0, 1, 1> xyy, rgg, stt;       \
  permutation<V, T, 1, 1, 1> yyy, ggg, ttt;       \
  permutation<V, T, 2, 1, 1> zyy, bgg, ptt;       \
  permutation<V, T, 0, 2, 1> xzy, rbg, spt;       \
  permutation<V, T, 1, 2, 1> yzy, gbg, tpt;       \
  permutation<V, T, 2, 2, 1> zzy, bbg, ppt;       \
  permutation<V, T, 0, 0, 2> xxz, rrb, ssp;       \
  permutation<V, T, 1, 0, 2> yxz, grb, tsp;       \
  permutation<V, T, 2, 0, 2> zxz, brb, psp;       \
  permutation<V, T, 0, 1, 2> xyz, rgb, stp;       \
  permutation<V, T, 1, 1, 2> yyz, ggb, ttp;       \
  permutation<V, T, 2, 1, 2> zyz, bgb, ptp;       \
  permutation<V, T, 0, 2, 2> xzz, rbb, spp;       \
  permutation<V, T, 1, 2, 2> yzz, gbb, tpp;       \
  permutation<V, T, 2, 2, 2> zzz, bbb, ppp;       \
  permutation<V, T, 0, 0, 0, 0> xxxx, rrrr, ssss; \
  permutation<V, T, 1, 0, 0, 0> yxxx, grrr, tsss; \
  permutation<V, T, 2, 0, 0, 0> zxxx, brrr, psss; \
  permutation<V, T, 0, 1, 0, 0> xyxx, rgrr, stss; \
  permutation<V, T, 1, 1, 0, 0> yyxx, ggrr, ttss; \
  permutation<V, T, 2, 1, 0, 0> zyxx, bgrr, ptss; \
  permutation<V, T, 0, 2, 0, 0> xzxx, rbrr, spss; \
  permutation<V, T, 1, 2, 0, 0> yzxx, gbrr, tpss; \
  permutation<V, T, 2, 2, 0, 0> zzxx, bbrr, ppss; \
  permutation<V, T, 0, 0, 1, 0> xxyx, rrgr, ssts; \
  permutation<V, T, 1, 0, 1, 0> yxyx, grgr, tsts; \
  permutation<V, T, 2, 0, 1, 0> zxyx, brgr, psts; \
  permutation<V, T, 0, 1, 1, 0> xyyx, rggr, stts; \
  permutation<V, T, 1, 1, 1, 0> yyyx, gggr, ttts; \
  permutation<V, T, 2, 1, 1, 0> zyyx, bggr, ptts; \
  permutation<V, T, 0, 2, 1, 0> xzyx, rbgr, spts; \
  permutation<V, T, 1, 2, 1, 0> yzyx, gbgr, tpts; \
  permutation<V, T, 2, 2, 1, 0> zzyx, bbgr, ppts; \
  permutation<V, T, 0, 0, 2, 0> xxzx, rrbr, ssps; \
  permutation<V, T, 1, 0, 2, 0> yxzx, grbr, tsps; \
  permutation<V, T, 2, 0, 2, 0> zxzx, brbr, psps; \
  permutation<V, T, 0, 1, 2, 0> xyzx, rgbr, stps; \
  permutation<V, T, 1, 1, 2, 0> yyzx, ggbr, ttps; \
  permutation<V, T, 2, 1, 2, 0> zyzx, bgbr, ptps; \
  permutation<V, T, 0, 2, 2, 0> xzzx, rbbr, spps; \
  permutation<V, T, 1, 2, 2, 0> yzzx, gbbr, tpps; \
  permutation<V, T, 2, 2, 2, 0> zzzx, bbbr, ppps; \
  permutation<V, T, 0, 0, 0, 1> xxxy, rrrg, ssst; \
  permutation<V, T, 1, 0, 0, 1> yxxy, grrg, tsst; \
  permutation<V, T, 2, 0, 0, 1> zxxy, brrg, psst; \
  permutation<V, T, 0, 1, 0, 1> xyxy, rgrg, stst; \
  permutation<V, T, 1, 1, 0, 1> yyxy, ggrg, ttst; \
  permutation<V, T, 2, 1, 0, 1> zyxy, bgrg, ptst; \
  permutation<V, T, 0, 2, 0, 1> xzxy, rbrg, spst; \
  permutation<V, T, 1, 2, 0, 1> yzxy, gbrg, tpst; \
  permutation<V, T, 2, 2, 0, 1> zzxy, bbrg, ppst; \
  permutation<V, T, 0, 0, 1, 1> xxyy, rrgg, sstt; \
  permutation<V, T, 1, 0, 1, 1> yxyy, grgg, tstt; \
  permutation<V, T, 2, 0, 1, 1> zxyy, brgg, pstt; \
  permutation<V, T, 0, 1, 1, 1> xyyy, rggg, sttt; \
  permutation<V, T, 1, 1, 1, 1> yyyy, gggg, tttt; \
  permutation<V, T, 2, 1, 1, 1> zyyy, bggg, pttt; \
  permutation<V, T, 0, 2, 1, 1> xzyy, rbgg, sptt; \
  permutation<V, T, 1, 2, 1, 1> yzyy, gbgg, tptt; \
  permutation<V, T, 2, 2, 1, 1> zzyy, bbgg, pptt; \
  permutation<V, T, 0, 0, 2, 1> xxzy, rrbg, sspt; \
  permutation<V, T, 1, 0, 2, 1> yxzy, grbg, tspt; \
  permutation<V, T, 2, 0, 2, 1> zxzy, brbg, pspt; \
  permutation<V, T, 0, 1, 2, 1> xyzy, rgbg, stpt; \
  permutation<V, T, 1, 1, 2, 1> yyzy, ggbg, ttpt; \
  permutation<V, T, 2, 1, 2, 1> zyzy, bgbg, ptpt; \
  permutation<V, T, 0, 2, 2, 1> xzzy, rbbg, sppt; \
  permutation<V, T, 1, 2, 2, 1> yzzy, gbbg, tppt; \
  permutation<V, T, 2, 2, 2, 1> zzzy, bbbg, pppt; \
  permutation<V, T, 0, 0, 0, 2> xxxz, rrrb, sssp; \
  permutation<V, T, 1, 0, 0, 2> yxxz, grrb, tssp; \
  permutation<V, T, 2, 0, 0, 2> zxxz, brrb, pssp; \
  permutation<V, T, 0, 1, 0, 2> xyxz, rgrb, stsp; \
  permutation<V, T, 1, 1, 0, 2> yyxz, ggrb, ttsp; \
  permutation<V, T, 2, 1, 0, 2> zyxz, bgrb, ptsp; \
  permutation<V, T, 0, 2, 0, 2> xzxz, rbrb, spsp; \
  permutation<V, T, 1, 2, 0, 2> yzxz, gbrb, tpsp; \
  permutation<V, T, 2, 2, 0, 2> zzxz, bbrb, ppsp; \
  permutation<V, T, 0, 0, 1, 2> xxyz, rrgb, sstp; \
  permutation<V, T, 1, 0, 1, 2> yxyz, grgb, tstp; \
  permutation<V, T, 2, 0, 1, 2> zxyz, brgb, pstp; \
  permutation<V, T, 0, 1, 1, 2> xyyz, rggb, sttp; \
  permutation<V, T, 1, 1, 1, 2> yyyz, gggb, tttp; \
  permutation<V, T, 2, 1, 1, 2> zyyz, bggb, pttp; \
  permutation<V, T, 0, 2, 1, 2> xzyz, rbgb, sptp; \
  permutation<V, T, 1, 2, 1, 2> yzyz, gbgb, tptp; \
  permutation<V, T, 2, 2, 1, 2> zzyz, bbgb, pptp; \
  permutation<V, T, 0, 0, 2, 2> xxzz, rrbb, sspp; \
  permutation<V, T, 1, 0, 2, 2> yxzz, grbb, tspp; \
  permutation<V, T, 2, 0, 2, 2> zxzz, brbb, pspp; \
  permutation<V, T, 0, 1, 2, 2> xyzz, rgbb, stpp; \
  permutation<V, T, 1, 1, 2, 2> yyzz, ggbb, ttpp; \
  permutation<V, T, 2, 1, 2, 2> zyzz, bgbb, ptpp; \
  permutation<V, T, 0, 2, 2, 2> xzzz, rbbb, sppp; \
  permutation<V, T, 1, 2, 2, 2> yzzz, gbbb, tppp; \
  permutation<V, T, 2, 2, 2, 2> zzzz, bbbb, pppp;

#define ALL_V4_PERMUTATIONS(V, T)                 \
  permutation<V, T, 0, 0> xx, rr, ss;             \
  permutation<V, T, 1, 0> yx, gr, ts;             \
  permutation<V, T, 2, 0> zx, br, ps;             \
  permutation<V, T, 3, 0> wx, ar, qs;             \
  permutation<V, T, 0, 1> xy, rg, st;             \
  permutation<V, T, 1, 1> yy, gg, tt;             \
  permutation<V, T, 2, 1> zy, bg, pt;             \
  permutation<V, T, 3, 1> wy, ag, qt;             \
  permutation<V, T, 0, 2> xz, rb, sp;             \
  permutation<V, T, 1, 2> yz, gb, tp;             \
  permutation<V, T, 2, 2> zz, bb, pp;             \
  permutation<V, T, 3, 2> wz, ab, qp;             \
  permutation<V, T, 0, 3> xw, ra, sq;             \
  permutation<V, T, 1, 3> yw, ga, tq;             \
  permutation<V, T, 2, 3> zw, ba, pq;             \
  permutation<V, T, 3, 3> ww, aa, qq;             \
  permutation<V, T, 0, 0, 0> xxx, rrr, sss;       \
  permutation<V, T, 1, 0, 0> yxx, grr, tss;       \
  permutation<V, T, 2, 0, 0> zxx, brr, pss;       \
  permutation<V, T, 3, 0, 0> wxx, arr, qss;       \
  permutation<V, T, 0, 1, 0> xyx, rgr, sts;       \
  permutation<V, T, 1, 1, 0> yyx, ggr, tts;       \
  permutation<V, T, 2, 1, 0> zyx, bgr, pts;       \
  permutation<V, T, 3, 1, 0> wyx, agr, qts;       \
  permutation<V, T, 0, 2, 0> xzx, rbr, sps;       \
  permutation<V, T, 1, 2, 0> yzx, gbr, tps;       \
  permutation<V, T, 2, 2, 0> zzx, bbr, pps;       \
  permutation<V, T, 3, 2, 0> wzx, abr, qps;       \
  permutation<V, T, 0, 3, 0> xwx, rar, sqs;       \
  permutation<V, T, 1, 3, 0> ywx, gar, tqs;       \
  permutation<V, T, 2, 3, 0> zwx, bar, pqs;       \
  permutation<V, T, 3, 3, 0> wwx, aar, qqs;       \
  permutation<V, T, 0, 0, 1> xxy, rrg, sst;       \
  permutation<V, T, 1, 0, 1> yxy, grg, tst;       \
  permutation<V, T, 2, 0, 1> zxy, brg, pst;       \
  permutation<V, T, 3, 0, 1> wxy, arg, qst;       \
  permutation<V, T, 0, 1, 1> xyy, rgg, stt;       \
  permutation<V, T, 1, 1, 1> yyy, ggg, ttt;       \
  permutation<V, T, 2, 1, 1> zyy, bgg, ptt;       \
  permutation<V, T, 3, 1, 1> wyy, agg, qtt;       \
  permutation<V, T, 0, 2, 1> xzy, rbg, spt;       \
  permutation<V, T, 1, 2, 1> yzy, gbg, tpt;       \
  permutation<V, T, 2, 2, 1> zzy, bbg, ppt;       \
  permutation<V, T, 3, 2, 1> wzy, abg, qpt;       \
  permutation<V, T, 0, 3, 1> xwy, rag, sqt;       \
  permutation<V, T, 1, 3, 1> ywy, gag, tqt;       \
  permutation<V, T, 2, 3, 1> zwy, bag, pqt;       \
  permutation<V, T, 3, 3, 1> wwy, aag, qqt;       \
  permutation<V, T, 0, 0, 2> xxz, rrb, ssp;       \
  permutation<V, T, 1, 0, 2> yxz, grb, tsp;       \
  permutation<V, T, 2, 0, 2> zxz, brb, psp;       \
  permutation<V, T, 3, 0, 2> wxz, arb, qsp;       \
  permutation<V, T, 0, 1, 2> xyz, rgb, stp;       \
  permutation<V, T, 1, 1, 2> yyz, ggb, ttp;       \
  permutation<V, T, 2, 1, 2> zyz, bgb, ptp;       \
  permutation<V, T, 3, 1, 2> wyz, agb, qtp;       \
  permutation<V, T, 0, 2, 2> xzz, rbb, spp;       \
  permutation<V, T, 1, 2, 2> yzz, gbb, tpp;       \
  permutation<V, T, 2, 2, 2> zzz, bbb, ppp;       \
  permutation<V, T, 3, 2, 2> wzz, abb, qpp;       \
  permutation<V, T, 0, 3, 2> xwz, rab, sqp;       \
  permutation<V, T, 1, 3, 2> ywz, gab, tqp;       \
  permutation<V, T, 2, 3, 2> zwz, bab, pqp;       \
  permutation<V, T, 3, 3, 2> wwz, aab, qqp;       \
  permutation<V, T, 0, 0, 3> xxw, rra, ssq;       \
  permutation<V, T, 1, 0, 3> yxw, gra, tsq;       \
  permutation<V, T, 2, 0, 3> zxw, bra, psq;       \
  permutation<V, T, 3, 0, 3> wxw, ara, qsq;       \
  permutation<V, T, 0, 1, 3> xyw, rga, stq;       \
  permutation<V, T, 1, 1, 3> yyw, gga, ttq;       \
  permutation<V, T, 2, 1, 3> zyw, bga, ptq;       \
  permutation<V, T, 3, 1, 3> wyw, aga, qtq;       \
  permutation<V, T, 0, 2, 3> xzw, rba, spq;       \
  permutation<V, T, 1, 2, 3> yzw, gba, tpq;       \
  permutation<V, T, 2, 2, 3> zzw, bba, ppq;       \
  permutation<V, T, 3, 2, 3> wzw, aba, qpq;       \
  permutation<V, T, 0, 3, 3> xww, raa, sqq;       \
  permutation<V, T, 1, 3, 3> yww, gaa, tqq;       \
  permutation<V, T, 2, 3, 3> zww, baa, pqq;       \
  permutation<V, T, 3, 3, 3> www, aaa, qqq;       \
  permutation<V, T, 0, 0, 0, 0> xxxx, rrrr, ssss; \
  permutation<V, T, 1, 0, 0, 0> yxxx, grrr, tsss; \
  permutation<V, T, 2, 0, 0, 0> zxxx, brrr, psss; \
  permutation<V, T, 3, 0, 0, 0> wxxx, arrr, qsss; \
  permutation<V, T, 0, 1, 0, 0> xyxx, rgrr, stss; \
  permutation<V, T, 1, 1, 0, 0> yyxx, ggrr, ttss; \
  permutation<V, T, 2, 1, 0, 0> zyxx, bgrr, ptss; \
  permutation<V, T, 3, 1, 0, 0> wyxx, agrr, qtss; \
  permutation<V, T, 0, 2, 0, 0> xzxx, rbrr, spss; \
  permutation<V, T, 1, 2, 0, 0> yzxx, gbrr, tpss; \
  permutation<V, T, 2, 2, 0, 0> zzxx, bbrr, ppss; \
  permutation<V, T, 3, 2, 0, 0> wzxx, abrr, qpss; \
  permutation<V, T, 0, 3, 0, 0> xwxx, rarr, sqss; \
  permutation<V, T, 1, 3, 0, 0> ywxx, garr, tqss; \
  permutation<V, T, 2, 3, 0, 0> zwxx, barr, pqss; \
  permutation<V, T, 3, 3, 0, 0> wwxx, aarr, qqss; \
  permutation<V, T, 0, 0, 1, 0> xxyx, rrgr, ssts; \
  permutation<V, T, 1, 0, 1, 0> yxyx, grgr, tsts; \
  permutation<V, T, 2, 0, 1, 0> zxyx, brgr, psts; \
  permutation<V, T, 3, 0, 1, 0> wxyx, argr, qsts; \
  permutation<V, T, 0, 1, 1, 0> xyyx, rggr, stts; \
  permutation<V, T, 1, 1, 1, 0> yyyx, gggr, ttts; \
  permutation<V, T, 2, 1, 1, 0> zyyx, bggr, ptts; \
  permutation<V, T, 3, 1, 1, 0> wyyx, aggr, qtts; \
  permutation<V, T, 0, 2, 1, 0> xzyx, rbgr, spts; \
  permutation<V, T, 1, 2, 1, 0> yzyx, gbgr, tpts; \
  permutation<V, T, 2, 2, 1, 0> zzyx, bbgr, ppts; \
  permutation<V, T, 3, 2, 1, 0> wzyx, abgr, qpts; \
  permutation<V, T, 0, 3, 1, 0> xwyx, ragr, sqts; \
  permutation<V, T, 1, 3, 1, 0> ywyx, gagr, tqts; \
  permutation<V, T, 2, 3, 1, 0> zwyx, bagr, pqts; \
  permutation<V, T, 3, 3, 1, 0> wwyx, aagr, qqts; \
  permutation<V, T, 0, 0, 2, 0> xxzx, rrbr, ssps; \
  permutation<V, T, 1, 0, 2, 0> yxzx, grbr, tsps; \
  permutation<V, T, 2, 0, 2, 0> zxzx, brbr, psps; \
  permutation<V, T, 3, 0, 2, 0> wxzx, arbr, qsps; \
  permutation<V, T, 0, 1, 2, 0> xyzx, rgbr, stps; \
  permutation<V, T, 1, 1, 2, 0> yyzx, ggbr, ttps; \
  permutation<V, T, 2, 1, 2, 0> zyzx, bgbr, ptps; \
  permutation<V, T, 3, 1, 2, 0> wyzx, agbr, qtps; \
  permutation<V, T, 0, 2, 2, 0> xzzx, rbbr, spps; \
  permutation<V, T, 1, 2, 2, 0> yzzx, gbbr, tpps; \
  permutation<V, T, 2, 2, 2, 0> zzzx, bbbr, ppps; \
  permutation<V, T, 3, 2, 2, 0> wzzx, abbr, qpps; \
  permutation<V, T, 0, 3, 2, 0> xwzx, rabr, sqps; \
  permutation<V, T, 1, 3, 2, 0> ywzx, gabr, tqps; \
  permutation<V, T, 2, 3, 2, 0> zwzx, babr, pqps; \
  permutation<V, T, 3, 3, 2, 0> wwzx, aabr, qqps; \
  permutation<V, T, 0, 0, 3, 0> xxwx, rrar, ssqs; \
  permutation<V, T, 1, 0, 3, 0> yxwx, grar, tsqs; \
  permutation<V, T, 2, 0, 3, 0> zxwx, brar, psqs; \
  permutation<V, T, 3, 0, 3, 0> wxwx, arar, qsqs; \
  permutation<V, T, 0, 1, 3, 0> xywx, rgar, stqs; \
  permutation<V, T, 1, 1, 3, 0> yywx, ggar, ttqs; \
  permutation<V, T, 2, 1, 3, 0> zywx, bgar, ptqs; \
  permutation<V, T, 3, 1, 3, 0> wywx, agar, qtqs; \
  permutation<V, T, 0, 2, 3, 0> xzwx, rbar, spqs; \
  permutation<V, T, 1, 2, 3, 0> yzwx, gbar, tpqs; \
  permutation<V, T, 2, 2, 3, 0> zzwx, bbar, ppqs; \
  permutation<V, T, 3, 2, 3, 0> wzwx, abar, qpqs; \
  permutation<V, T, 0, 3, 3, 0> xwwx, raar, sqqs; \
  permutation<V, T, 1, 3, 3, 0> ywwx, gaar, tqqs; \
  permutation<V, T, 2, 3, 3, 0> zwwx, baar, pqqs; \
  permutation<V, T, 3, 3, 3, 0> wwwx, aaar, qqqs; \
  permutation<V, T, 0, 0, 0, 1> xxxy, rrrg, ssst; \
  permutation<V, T, 1, 0, 0, 1> yxxy, grrg, tsst; \
  permutation<V, T, 2, 0, 0, 1> zxxy, brrg, psst; \
  permutation<V, T, 3, 0, 0, 1> wxxy, arrg, qsst; \
  permutation<V, T, 0, 1, 0, 1> xyxy, rgrg, stst; \
  permutation<V, T, 1, 1, 0, 1> yyxy, ggrg, ttst; \
  permutation<V, T, 2, 1, 0, 1> zyxy, bgrg, ptst; \
  permutation<V, T, 3, 1, 0, 1> wyxy, agrg, qtst; \
  permutation<V, T, 0, 2, 0, 1> xzxy, rbrg, spst; \
  permutation<V, T, 1, 2, 0, 1> yzxy, gbrg, tpst; \
  permutation<V, T, 2, 2, 0, 1> zzxy, bbrg, ppst; \
  permutation<V, T, 3, 2, 0, 1> wzxy, abrg, qpst; \
  permutation<V, T, 0, 3, 0, 1> xwxy, rarg, sqst; \
  permutation<V, T, 1, 3, 0, 1> ywxy, garg, tqst; \
  permutation<V, T, 2, 3, 0, 1> zwxy, barg, pqst; \
  permutation<V, T, 3, 3, 0, 1> wwxy, aarg, qqst; \
  permutation<V, T, 0, 0, 1, 1> xxyy, rrgg, sstt; \
  permutation<V, T, 1, 0, 1, 1> yxyy, grgg, tstt; \
  permutation<V, T, 2, 0, 1, 1> zxyy, brgg, pstt; \
  permutation<V, T, 3, 0, 1, 1> wxyy, argg, qstt; \
  permutation<V, T, 0, 1, 1, 1> xyyy, rggg, sttt; \
  permutation<V, T, 1, 1, 1, 1> yyyy, gggg, tttt; \
  permutation<V, T, 2, 1, 1, 1> zyyy, bggg, pttt; \
  permutation<V, T, 3, 1, 1, 1> wyyy, aggg, qttt; \
  permutation<V, T, 0, 2, 1, 1> xzyy, rbgg, sptt; \
  permutation<V, T, 1, 2, 1, 1> yzyy, gbgg, tptt; \
  permutation<V, T, 2, 2, 1, 1> zzyy, bbgg, pptt; \
  permutation<V, T, 3, 2, 1, 1> wzyy, abgg, qptt; \
  permutation<V, T, 0, 3, 1, 1> xwyy, ragg, sqtt; \
  permutation<V, T, 1, 3, 1, 1> ywyy, gagg, tqtt; \
  permutation<V, T, 2, 3, 1, 1> zwyy, bagg, pqtt; \
  permutation<V, T, 3, 3, 1, 1> wwyy, aagg, qqtt; \
  permutation<V, T, 0, 0, 2, 1> xxzy, rrbg, sspt; \
  permutation<V, T, 1, 0, 2, 1> yxzy, grbg, tspt; \
  permutation<V, T, 2, 0, 2, 1> zxzy, brbg, pspt; \
  permutation<V, T, 3, 0, 2, 1> wxzy, arbg, qspt; \
  permutation<V, T, 0, 1, 2, 1> xyzy, rgbg, stpt; \
  permutation<V, T, 1, 1, 2, 1> yyzy, ggbg, ttpt; \
  permutation<V, T, 2, 1, 2, 1> zyzy, bgbg, ptpt; \
  permutation<V, T, 3, 1, 2, 1> wyzy, agbg, qtpt; \
  permutation<V, T, 0, 2, 2, 1> xzzy, rbbg, sppt; \
  permutation<V, T, 1, 2, 2, 1> yzzy, gbbg, tppt; \
  permutation<V, T, 2, 2, 2, 1> zzzy, bbbg, pppt; \
  permutation<V, T, 3, 2, 2, 1> wzzy, abbg, qppt; \
  permutation<V, T, 0, 3, 2, 1> xwzy, rabg, sqpt; \
  permutation<V, T, 1, 3, 2, 1> ywzy, gabg, tqpt; \
  permutation<V, T, 2, 3, 2, 1> zwzy, babg, pqpt; \
  permutation<V, T, 3, 3, 2, 1> wwzy, aabg, qqpt; \
  permutation<V, T, 0, 0, 3, 1> xxwy, rrag, ssqt; \
  permutation<V, T, 1, 0, 3, 1> yxwy, grag, tsqt; \
  permutation<V, T, 2, 0, 3, 1> zxwy, brag, psqt; \
  permutation<V, T, 3, 0, 3, 1> wxwy, arag, qsqt; \
  permutation<V, T, 0, 1, 3, 1> xywy, rgag, stqt; \
  permutation<V, T, 1, 1, 3, 1> yywy, ggag, ttqt; \
  permutation<V, T, 2, 1, 3, 1> zywy, bgag, ptqt; \
  permutation<V, T, 3, 1, 3, 1> wywy, agag, qtqt; \
  permutation<V, T, 0, 2, 3, 1> xzwy, rbag, spqt; \
  permutation<V, T, 1, 2, 3, 1> yzwy, gbag, tpqt; \
  permutation<V, T, 2, 2, 3, 1> zzwy, bbag, ppqt; \
  permutation<V, T, 3, 2, 3, 1> wzwy, abag, qpqt; \
  permutation<V, T, 0, 3, 3, 1> xwwy, raag, sqqt; \
  permutation<V, T, 1, 3, 3, 1> ywwy, gaag, tqqt; \
  permutation<V, T, 2, 3, 3, 1> zwwy, baag, pqqt; \
  permutation<V, T, 3, 3, 3, 1> wwwy, aaag, qqqt; \
  permutation<V, T, 0, 0, 0, 2> xxxz, rrrb, sssp; \
  permutation<V, T, 1, 0, 0, 2> yxxz, grrb, tssp; \
  permutation<V, T, 2, 0, 0, 2> zxxz, brrb, pssp; \
  permutation<V, T, 3, 0, 0, 2> wxxz, arrb, qssp; \
  permutation<V, T, 0, 1, 0, 2> xyxz, rgrb, stsp; \
  permutation<V, T, 1, 1, 0, 2> yyxz, ggrb, ttsp; \
  permutation<V, T, 2, 1, 0, 2> zyxz, bgrb, ptsp; \
  permutation<V, T, 3, 1, 0, 2> wyxz, agrb, qtsp; \
  permutation<V, T, 0, 2, 0, 2> xzxz, rbrb, spsp; \
  permutation<V, T, 1, 2, 0, 2> yzxz, gbrb, tpsp; \
  permutation<V, T, 2, 2, 0, 2> zzxz, bbrb, ppsp; \
  permutation<V, T, 3, 2, 0, 2> wzxz, abrb, qpsp; \
  permutation<V, T, 0, 3, 0, 2> xwxz, rarb, sqsp; \
  permutation<V, T, 1, 3, 0, 2> ywxz, garb, tqsp; \
  permutation<V, T, 2, 3, 0, 2> zwxz, barb, pqsp; \
  permutation<V, T, 3, 3, 0, 2> wwxz, aarb, qqsp; \
  permutation<V, T, 0, 0, 1, 2> xxyz, rrgb, sstp; \
  permutation<V, T, 1, 0, 1, 2> yxyz, grgb, tstp; \
  permutation<V, T, 2, 0, 1, 2> zxyz, brgb, pstp; \
  permutation<V, T, 3, 0, 1, 2> wxyz, argb, qstp; \
  permutation<V, T, 0, 1, 1, 2> xyyz, rggb, sttp; \
  permutation<V, T, 1, 1, 1, 2> yyyz, gggb, tttp; \
  permutation<V, T, 2, 1, 1, 2> zyyz, bggb, pttp; \
  permutation<V, T, 3, 1, 1, 2> wyyz, aggb, qttp; \
  permutation<V, T, 0, 2, 1, 2> xzyz, rbgb, sptp; \
  permutation<V, T, 1, 2, 1, 2> yzyz, gbgb, tptp; \
  permutation<V, T, 2, 2, 1, 2> zzyz, bbgb, pptp; \
  permutation<V, T, 3, 2, 1, 2> wzyz, abgb, qptp; \
  permutation<V, T, 0, 3, 1, 2> xwyz, ragb, sqtp; \
  permutation<V, T, 1, 3, 1, 2> ywyz, gagb, tqtp; \
  permutation<V, T, 2, 3, 1, 2> zwyz, bagb, pqtp; \
  permutation<V, T, 3, 3, 1, 2> wwyz, aagb, qqtp; \
  permutation<V, T, 0, 0, 2, 2> xxzz, rrbb, sspp; \
  permutation<V, T, 1, 0, 2, 2> yxzz, grbb, tspp; \
  permutation<V, T, 2, 0, 2, 2> zxzz, brbb, pspp; \
  permutation<V, T, 3, 0, 2, 2> wxzz, arbb, qspp; \
  permutation<V, T, 0, 1, 2, 2> xyzz, rgbb, stpp; \
  permutation<V, T, 1, 1, 2, 2> yyzz, ggbb, ttpp; \
  permutation<V, T, 2, 1, 2, 2> zyzz, bgbb, ptpp; \
  permutation<V, T, 3, 1, 2, 2> wyzz, agbb, qtpp; \
  permutation<V, T, 0, 2, 2, 2> xzzz, rbbb, sppp; \
  permutation<V, T, 1, 2, 2, 2> yzzz, gbbb, tppp; \
  permutation<V, T, 2, 2, 2, 2> zzzz, bbbb, pppp; \
  permutation<V, T, 3, 2, 2, 2> wzzz, abbb, qppp; \
  permutation<V, T, 0, 3, 2, 2> xwzz, rabb, sqpp; \
  permutation<V, T, 1, 3, 2, 2> ywzz, gabb, tqpp; \
  permutation<V, T, 2, 3, 2, 2> zwzz, babb, pqpp; \
  permutation<V, T, 3, 3, 2, 2> wwzz, aabb, qqpp; \
  permutation<V, T, 0, 0, 3, 2> xxwz, rrab, ssqp; \
  permutation<V, T, 1, 0, 3, 2> yxwz, grab, tsqp; \
  permutation<V, T, 2, 0, 3, 2> zxwz, brab, psqp; \
  permutation<V, T, 3, 0, 3, 2> wxwz, arab, qsqp; \
  permutation<V, T, 0, 1, 3, 2> xywz, rgab, stqp; \
  permutation<V, T, 1, 1, 3, 2> yywz, ggab, ttqp; \
  permutation<V, T, 2, 1, 3, 2> zywz, bgab, ptqp; \
  permutation<V, T, 3, 1, 3, 2> wywz, agab, qtqp; \
  permutation<V, T, 0, 2, 3, 2> xzwz, rbab, spqp; \
  permutation<V, T, 1, 2, 3, 2> yzwz, gbab, tpqp; \
  permutation<V, T, 2, 2, 3, 2> zzwz, bbab, ppqp; \
  permutation<V, T, 3, 2, 3, 2> wzwz, abab, qpqp; \
  permutation<V, T, 0, 3, 3, 2> xwwz, raab, sqqp; \
  permutation<V, T, 1, 3, 3, 2> ywwz, gaab, tqqp; \
  permutation<V, T, 2, 3, 3, 2> zwwz, baab, pqqp; \
  permutation<V, T, 3, 3, 3, 2> wwwz, aaab, qqqp; \
  permutation<V, T, 0, 0, 0, 3> xxxw, rrra, sssq; \
  permutation<V, T, 1, 0, 0, 3> yxxw, grra, tssq; \
  permutation<V, T, 2, 0, 0, 3> zxxw, brra, pssq; \
  permutation<V, T, 3, 0, 0, 3> wxxw, arra, qssq; \
  permutation<V, T, 0, 1, 0, 3> xyxw, rgra, stsq; \
  permutation<V, T, 1, 1, 0, 3> yyxw, ggra, ttsq; \
  permutation<V, T, 2, 1, 0, 3> zyxw, bgra, ptsq; \
  permutation<V, T, 3, 1, 0, 3> wyxw, agra, qtsq; \
  permutation<V, T, 0, 2, 0, 3> xzxw, rbra, spsq; \
  permutation<V, T, 1, 2, 0, 3> yzxw, gbra, tpsq; \
  permutation<V, T, 2, 2, 0, 3> zzxw, bbra, ppsq; \
  permutation<V, T, 3, 2, 0, 3> wzxw, abra, qpsq; \
  permutation<V, T, 0, 3, 0, 3> xwxw, rara, sqsq; \
  permutation<V, T, 1, 3, 0, 3> ywxw, gara, tqsq; \
  permutation<V, T, 2, 3, 0, 3> zwxw, bara, pqsq; \
  permutation<V, T, 3, 3, 0, 3> wwxw, aara, qqsq; \
  permutation<V, T, 0, 0, 1, 3> xxyw, rrga, sstq; \
  permutation<V, T, 1, 0, 1, 3> yxyw, grga, tstq; \
  permutation<V, T, 2, 0, 1, 3> zxyw, brga, pstq; \
  permutation<V, T, 3, 0, 1, 3> wxyw, arga, qstq; \
  permutation<V, T, 0, 1, 1, 3> xyyw, rgga, sttq; \
  permutation<V, T, 1, 1, 1, 3> yyyw, ggga, tttq; \
  permutation<V, T, 2, 1, 1, 3> zyyw, bgga, pttq; \
  permutation<V, T, 3, 1, 1, 3> wyyw, agga, qttq; \
  permutation<V, T, 0, 2, 1, 3> xzyw, rbga, sptq; \
  permutation<V, T, 1, 2, 1, 3> yzyw, gbga, tptq; \
  permutation<V, T, 2, 2, 1, 3> zzyw, bbga, pptq; \
  permutation<V, T, 3, 2, 1, 3> wzyw, abga, qptq; \
  permutation<V, T, 0, 3, 1, 3> xwyw, raga, sqtq; \
  permutation<V, T, 1, 3, 1, 3> ywyw, gaga, tqtq; \
  permutation<V, T, 2, 3, 1, 3> zwyw, baga, pqtq; \
  permutation<V, T, 3, 3, 1, 3> wwyw, aaga, qqtq; \
  permutation<V, T, 0, 0, 2, 3> xxzw, rrba, sspq; \
  permutation<V, T, 1, 0, 2, 3> yxzw, grba, tspq; \
  permutation<V, T, 2, 0, 2, 3> zxzw, brba, pspq; \
  permutation<V, T, 3, 0, 2, 3> wxzw, arba, qspq; \
  permutation<V, T, 0, 1, 2, 3> xyzw, rgba, stpq; \
  permutation<V, T, 1, 1, 2, 3> yyzw, ggba, ttpq; \
  permutation<V, T, 2, 1, 2, 3> zyzw, bgba, ptpq; \
  permutation<V, T, 3, 1, 2, 3> wyzw, agba, qtpq; \
  permutation<V, T, 0, 2, 2, 3> xzzw, rbba, sppq; \
  permutation<V, T, 1, 2, 2, 3> yzzw, gbba, tppq; \
  permutation<V, T, 2, 2, 2, 3> zzzw, bbba, pppq; \
  permutation<V, T, 3, 2, 2, 3> wzzw, abba, qppq; \
  permutation<V, T, 0, 3, 2, 3> xwzw, raba, sqpq; \
  permutation<V, T, 1, 3, 2, 3> ywzw, gaba, tqpq; \
  permutation<V, T, 2, 3, 2, 3> zwzw, baba, pqpq; \
  permutation<V, T, 3, 3, 2, 3> wwzw, aaba, qqpq; \
  permutation<V, T, 0, 0, 3, 3> xxww, rraa, ssqq; \
  permutation<V, T, 1, 0, 3, 3> yxww, graa, tsqq; \
  permutation<V, T, 2, 0, 3, 3> zxww, braa, psqq; \
  permutation<V, T, 3, 0, 3, 3> wxww, araa, qsqq; \
  permutation<V, T, 0, 1, 3, 3> xyww, rgaa, stqq; \
  permutation<V, T, 1, 1, 3, 3> yyww, ggaa, ttqq; \
  permutation<V, T, 2, 1, 3, 3> zyww, bgaa, ptqq; \
  permutation<V, T, 3, 1, 3, 3> wyww, agaa, qtqq; \
  permutation<V, T, 0, 2, 3, 3> xzww, rbaa, spqq; \
  permutation<V, T, 1, 2, 3, 3> yzww, gbaa, tpqq; \
  permutation<V, T, 2, 2, 3, 3> zzww, bbaa, ppqq; \
  permutation<V, T, 3, 2, 3, 3> wzww, abaa, qpqq; \
  permutation<V, T, 0, 3, 3, 3> xwww, raaa, sqqq; \
  permutation<V, T, 1, 3, 3, 3> ywww, gaaa, tqqq; \
  permutation<V, T, 2, 3, 3, 3> zwww, baaa, pqqq; \
  permutation<V, T, 3, 3, 3, 3> wwww, aaaa, qqqq;

}  // namespace glsl

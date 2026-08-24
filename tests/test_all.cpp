#include <bits/stdc++.h>
#include <cassert>
#include <iostream>

// ----------------------------------------------------
// 1. 压制源文件中未返回 0 和 freopen 的警告
// 2. 将源文件中的 main 重命名，零修改源文件
// ----------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wunused-result"
#define main unused_template_main
#include "../template.cpp"
#undef main
#pragma GCC diagnostic pop

// ---------------- 线段树辅助函数（单点修改，区间和） ----------------
int seg_op(int a, int b) { return a + b; }
int seg_e() { return 0; }

// ---------------- 延迟线段树辅助函数（区间加，区间最大值） ----------------
int lazy_op(int a, int b) { return std::max(a, b); }
int lazy_e() { return -1e9; }
int lazy_mapping(int f, int x) { return x + f; }
int lazy_composition(int f, int g) { return f + g; }
int lazy_id() { return 0; }

// ---------------- 真正执行测试的 main ----------------
int main() {
    std::cout << "[CI] Running template instantiation & tests..." << std::endl;

    // 1. DSU 并查集
    {
        dsu d(10);
        d.merge(1, 2);
        d.merge(2, 3);
        assert(d.same(1, 3));
        assert(!d.same(1, 4));
        assert(d.size(1) == 3);
    }

    // 2. 树状数组 (BIT)
    {
        BIT<int> bit(10);
        bit.add(3, 5);
        bit.add(4, 2);
        assert(bit.sum(3) == 5);
        assert(bit.sum(3, 4) == 7);
    }

    // 3. 数论命名空间 (math)
    {
        assert(math::isprime(2));
        assert(math::isprime(998244353));
        assert(!math::isprime(4));
        assert(math::qmi(2, 10, 1000) == 24);
        assert(math::invmod(3, 7) == 5);
        auto pr = math::crt({2, 3}, {3, 5});
        assert(pr.fs == 8 && pr.sc == 15);
    }

    // 4. Barrett 模乘优化
    {
        barrett bt(998244353);
        assert(bt.mul(1000000, 2000000) == (1000000ULL * 2000000ULL) % 998244353);
    }

    // 5. 静态模数 static_modint
    {
        using mint = static_modint<998244353>;
        mint a = 2, b = 998244352;
        assert((a + b).val() == 1);
        assert((a * b).val() == 998244351);
        assert(a.pow(3).val() == 8);
        assert((a / a).val() == 1);
    }

    // 6. 动态模数 dynamic_modint
    {
        using dmint = dynamic_modint<0>;
        dmint::set_mod(1000000007);
        dmint a = 1000000006, b = 2;
        assert((a + b).val() == 1);
        assert((a * b).val() == 1000000005);
    }

    // 7. 单点修改区间查询线段树 segtree (区间和)
    {
        segtree<int, seg_op, seg_e> seg(5);
        seg.set(1, 10);
        seg.set(2, 20);
        assert(seg.prod(1, 2) == 30);
        assert(seg.all_prod() == 30);
    }

    // 8. 区间修改区间查询线段树 lazy_segtree (区间加，区间最大值)
    {
        // 初始全 0 的序列，长度为 5
        vector<int> init_val(6, 0);
        lazy_segtree<int, lazy_op, lazy_e, int, lazy_mapping, lazy_composition, lazy_id> lz(init_val);

        // [1, 3] 区间 +5 => 序列变为: [5, 5, 5, 0, 0]
        lz.apply(1, 3, 5);
        assert(lz.prod(1, 2) == 5);
        assert(lz.prod(4, 5) == 0);
        assert(lz.prod(1, 5) == 5);

        // [2, 4] 区间 +3 => 序列变为: [5, 8, 8, 3, 0]
        lz.apply(2, 4, 3);
        assert(lz.prod(1, 2) == 8);
        assert(lz.prod(2, 3) == 8);
        assert(lz.prod(4, 5) == 3);
    }

    // 9. 组合数 Comb_static / Comb_dynamic
    {
        Comb_static<998244353> cs(100, -1);
        assert(cs.comb(5, 2) == 10);
        assert(cs.comb(5, 6) == -1);

        Comb_dynamic<1> cd(100, 1000000007, -1);
        assert(cd.comb(6, 3) == 20);
    }

    // 10. 字符串算法 str (kmp / manacher)
    {
        auto nxt = str::kmp("ababcaba");
        assert(nxt.size() == 9);
        auto p = str::manacher("aba");
        assert(!p.empty());
    }

    // 11. 矩阵快速幂 Matrix
    {
        using mint = static_modint<998244353>;
        Matrix<mint> mat(2, 2);
        mat[1][1] = 1; mat[1][2] = 1;
        mat[2][1] = 1; mat[2][2] = 0;
        Matrix<mint> res = mat ^ 5;
        assert(res[1][2].val() == 5);
    }

    // 12. 随机数 rd
    {
        int r = rd::randint(1, 10);
        assert(r >= 1 && r <= 10);
    }
    {
        vector<int>g={1,2,5,4,3};
        ST<int, seg_op, seg_e>p(g);
        int res1=p.prod(1,3);
        int res2=p.prod(4,5);
        assert(res1==5&&res2==4);
    }
    std::cout << "[CI] All components instantiated and passed tests!" << std::endl;
    return 0;
}

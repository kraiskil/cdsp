//          Copyright Heikki Berg 2017 - 2018
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include <random>

#include <gtest/gtest.h>

#include <cdsp/complex.h>
#include <cdsp/dsp_types.h>
#include <cdsp/virtual_float.h>

TEST(virtual_float, creation)
{
    {
        cdsp::virtual_float<float> val{1.0f};
        float val_float = static_cast<float>(val);
        EXPECT_EQ(val_float, 1.0f);
    }
    {
        cdsp::virtual_float<float> val{7.0f};
        float val_float = static_cast<float>(val);
        EXPECT_EQ(val_float, 7.0f);
    }
    {
        q4_20 val{2.0f};
        cdsp::virtual_float<q4_20> valvf{val};
        EXPECT_EQ(static_cast<float>(valvf), 2.0f);
        EXPECT_EQ(static_cast<float>(valvf.mantissa()), 2.0f);
        EXPECT_EQ(valvf.exponent(), 0);
    }
    {
        q4_20 val{7.0f};
        cdsp::virtual_float<q4_20> valvf{val};
        EXPECT_EQ(static_cast<float>(valvf), 7.0f);
        EXPECT_EQ(static_cast<float>(valvf.mantissa()), 3.5f);
        EXPECT_EQ(valvf.exponent(), 1);
    }
    {
        q8_40 val{7.0f};
        cdsp::virtual_float<q8_40> valvf{val};
        EXPECT_EQ(static_cast<float>(valvf), 7.0f);
        EXPECT_EQ(static_cast<float>(valvf.mantissa()), 3.5f);
        EXPECT_EQ(valvf.exponent(), 1);
    }
    {
        cdsp::virtual_float<q4_20> val{3.0f};
        cdsp::virtual_float<q4_20> valvf{val};
        EXPECT_EQ(static_cast<float>(valvf), 3.0f);
        EXPECT_EQ(static_cast<float>(valvf.mantissa()), 3.0f);
        EXPECT_EQ(valvf.exponent(), 0);
    }
    {
        cdsp::virtual_float<q4_20> val{3.0f};
        cdsp::virtual_float<q4_20> valvf{std::move(val)};
        EXPECT_EQ(static_cast<float>(valvf), 3.0f);
        EXPECT_EQ(static_cast<float>(valvf.mantissa()), 3.0f);
        EXPECT_EQ(valvf.exponent(), 0);
    }
}

TEST(virtual_float, sum)
{

    {
        cdsp::virtual_float<float> f1(1.0f);
        cdsp::virtual_float<float> f2(2.0f);
        cdsp::virtual_float<float> f = f1 + f2;
        EXPECT_EQ(static_cast<float>(f), 3.0f);
    }
    {
        cdsp::virtual_float<q4_20> f1{1.0f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 + f2;
        EXPECT_EQ(static_cast<float>(f1), 1.0f);
        EXPECT_EQ(static_cast<float>(f2), 2.0f);
        EXPECT_EQ(static_cast<float>(f), 3.0f);
    }
    {
        cdsp::virtual_float<q8_40> f1{1.0f};
        cdsp::virtual_float<q8_40> f2{2.0f};
        cdsp::virtual_float<q8_40> f = f1 + f2;
        EXPECT_EQ(static_cast<float>(f1), 1.0f);
        EXPECT_EQ(static_cast<float>(f2), 2.0f);
        EXPECT_EQ(static_cast<float>(f), 3.0f);
    }
}

TEST(virtual_float, subtract)
{
    {
        cdsp::virtual_float<float> f1(1.0f);
        cdsp::virtual_float<float> f2(2.0f);
        cdsp::virtual_float<float> f = f1 - f2;
        EXPECT_EQ(static_cast<float>(f), -1.0f);
    }
    {
        cdsp::virtual_float<q4_20> f1{1.0f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 - f2;
        EXPECT_EQ(static_cast<float>(f), -1.0f);
    }
    {
        cdsp::virtual_float<q8_40> f1{1.0f};
        cdsp::virtual_float<q8_40> f2{2.0f};
        cdsp::virtual_float<q8_40> f = f1 - f2;
        EXPECT_EQ(static_cast<float>(f), -1.0f);
    }
}

TEST(virtual_float, negate)
{
    {
        cdsp::virtual_float<q4_20> f1{1.0f};
        cdsp::virtual_float<q4_20> f = -f1;
        EXPECT_EQ(static_cast<float>(f), -1.0f);
    }
    {
        cdsp::virtual_float<q8_40> f1{1.0f};
        cdsp::virtual_float<q8_40> f = -f1;
        EXPECT_EQ(static_cast<float>(f), -1.0f);
    }
}

TEST(virtual_float, multiply)
{
    {
        cdsp::virtual_float<q4_20> f1{1.0f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 * f2;
        EXPECT_EQ(static_cast<float>(f), 2.0f);
    }
    {
        cdsp::virtual_float<q4_20> f1{0.125f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 * f2;
        EXPECT_EQ(static_cast<float>(f), 0.250f);
    }
    {
        cdsp::virtual_float<q4_20> f1{0.34561825f};
        cdsp::virtual_float<q4_20> f2{1.5678196f};
        cdsp::virtual_float<q4_20> f = f1 * f2;
        EXPECT_FLOAT_EQ(static_cast<float>(f), 0.54186706f);
    }
    {
        cdsp::virtual_float<q8_40> f1{1.0f};
        cdsp::virtual_float<q8_40> f2{2.0f};
        cdsp::virtual_float<q8_40> f = f1 * f2;
        EXPECT_EQ(static_cast<float>(f), 2.0f);
    }
    {
        cdsp::virtual_float<q8_40> f1{0.34561825f};
        cdsp::virtual_float<q8_40> f2{1.5678196f};
        cdsp::virtual_float<q8_40> f = f1 * f2;
        EXPECT_FLOAT_EQ(static_cast<float>(f), 0.54186706f);
    }
}

TEST(virtual_float, division)
{
    {
        cdsp::virtual_float<q4_20> f1{1.0f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 / f2;
        EXPECT_EQ(static_cast<float>(f), 0.5f);
    }
    {
        cdsp::virtual_float<q4_20> f1{0.125f};
        cdsp::virtual_float<q4_20> f2{2.0f};
        cdsp::virtual_float<q4_20> f = f1 / f2;
        EXPECT_EQ(static_cast<float>(f), 0.0625f);

    }
    {
        cdsp::virtual_float<q4_20> f1{0.34561825f};
        cdsp::virtual_float<q4_20> f2{1.5678196f};
        cdsp::virtual_float<q4_20> f = f1 / f2;
        EXPECT_FLOAT_EQ(static_cast<float>(f), 0.22044516f);
    }
    {
        cdsp::virtual_float<q8_40> f1{0.34561825f};
        cdsp::virtual_float<q8_40> f2{1.5678196f};
        cdsp::virtual_float<q8_40> f = f1 / f2;
        EXPECT_FLOAT_EQ(static_cast<float>(f), 0.22044516f);
    }
}

TEST(virtual_float, assignment)
{
    {
        cdsp::virtual_float<float> e = 2.0f;
        EXPECT_EQ(static_cast<float>(e), 2.0f);
    }
    {
        cdsp::virtual_float<q4_20> e = q4_20{3.0f};
        EXPECT_EQ(static_cast<float>(e), 3.0f);
    }
    {
        cdsp::virtual_float<q4_20> f = q4_20{3.0f};
        cdsp::virtual_float<q8_40> e = f;
        EXPECT_EQ(static_cast<float>(e), 3.0f);
    }
    {
        cdsp::virtual_float<q8_40> f = q8_40{3.0f};
        cdsp::virtual_float<q4_20> e = f;
        EXPECT_EQ(static_cast<float>(e), 3.0f);
    }
}

TEST(virtual_float, comparison)
{
    {
        cdsp::virtual_float<float> a{1.0f};
        cdsp::virtual_float<float> b{0.0f};
        EXPECT_TRUE(a > b);
        EXPECT_TRUE(a >= b);
        EXPECT_FALSE(b > a);
        EXPECT_FALSE(b >= a);
        EXPECT_TRUE(b < a);
        EXPECT_TRUE(b <= a);
        EXPECT_FALSE(a < b);
        EXPECT_FALSE(a <= b);
        EXPECT_FALSE(a < a);
        EXPECT_FALSE(a > a);
        EXPECT_TRUE(a >= a);
        EXPECT_TRUE(a <= a);
        EXPECT_TRUE(a == a);
        EXPECT_FALSE(a != a);
        EXPECT_TRUE(a != b);
        EXPECT_TRUE(b != a);
    }
    {
        cdsp::virtual_float<q4_20> a{2.0f};
        cdsp::virtual_float<q4_20> b{1.0f};
        EXPECT_TRUE(a > b);
        EXPECT_TRUE(a >= b);
        EXPECT_FALSE(b > a);
        EXPECT_FALSE(b >= a);
        EXPECT_TRUE(b < a);
        EXPECT_TRUE(b <= a);
        EXPECT_FALSE(a < b);
        EXPECT_FALSE(a <= b);
        EXPECT_FALSE(a < a);
        EXPECT_FALSE(a > a);
        EXPECT_TRUE(a >= a);
        EXPECT_TRUE(a <= a);
        EXPECT_TRUE(a == a);
        EXPECT_FALSE(a != a);
        EXPECT_TRUE(a != b);
        EXPECT_TRUE(b != a);
    }
    {
        cdsp::virtual_float<q8_40> a{2.0f};
        cdsp::virtual_float<q8_40> b{1.0f};
        EXPECT_TRUE(a > b);
        EXPECT_TRUE(a >= b);
        EXPECT_FALSE(b > a);
        EXPECT_FALSE(b >= a);
        EXPECT_TRUE(b < a);
        EXPECT_TRUE(b <= a);
        EXPECT_FALSE(a < b);
        EXPECT_FALSE(a <= b);
        EXPECT_FALSE(a < a);
        EXPECT_FALSE(a > a);
        EXPECT_TRUE(a >= a);
        EXPECT_TRUE(a <= a);
        EXPECT_TRUE(a == a);
        EXPECT_FALSE(a != a);
        EXPECT_TRUE(a != b);
        EXPECT_TRUE(b != a);
    }
}

TEST(virtual_float, square_root)
{
    {
        cdsp::virtual_float<float> a{1.0f};
        cdsp::virtual_float<float> b = sqrt(a);
        EXPECT_EQ(static_cast<float>(b), 1.0f);
    }
    {
        cdsp::virtual_float<float> a{2.0f};
        cdsp::virtual_float<float> b = sqrt(a);
        EXPECT_EQ(static_cast<float>(b), std::sqrt(2.0f));
    }
    {
        cdsp::virtual_float<q4_20> a{2.0f};
        EXPECT_EQ(static_cast<float>(a), 2.0f);
        cdsp::virtual_float<q4_20> b = sqrt(a);
        EXPECT_FLOAT_EQ(static_cast<float>(b), std::sqrt(2.0f));
    }
    {
        cdsp::virtual_float<q4_20> a{3.5783958f};
        EXPECT_FLOAT_EQ(static_cast<float>(a), 3.5783958f);
        cdsp::virtual_float<q4_20> b = sqrt(a);
        EXPECT_FLOAT_EQ(static_cast<float>(b), std::sqrt(3.5783958f));
    }
    {
        cdsp::virtual_float<q4_20> a{1.349885940551758f};
        EXPECT_FLOAT_EQ(static_cast<float>(a), 1.349885940551758f);
        cdsp::virtual_float<q4_20> b = sqrt(a);
        EXPECT_NEAR(static_cast<float>(b), std::sqrt(1.349885940551758f), 0.00001);
    }
#if defined(CNL_INT128_ENABLED)
    {
        cdsp::virtual_float<q8_40> a{1.349885940551758f};
        EXPECT_FLOAT_EQ(static_cast<float>(a), 1.349885940551758f);
        cdsp::virtual_float<q8_40> b = sqrt(a);
        EXPECT_NEAR(static_cast<float>(b), std::sqrt(1.349885940551758f), 0.00001);
    }
#endif
}

TEST(virtual_float, from_virtual_float)
{
    {
        cdsp::virtual_float<q4_20> a{2.0f};
        q4_20 b = static_cast<q4_20>(a);
        EXPECT_EQ(static_cast<float>(b), 2.0f);
    }
    {
        cdsp::virtual_float<q8_40> a{2.0f};
        q8_40 b = static_cast<q8_40>(a);
        EXPECT_EQ(static_cast<float>(b), 2.0f);
    }
    {
        cdsp::virtual_float<q8_40> a{2.0f};
        q4_20 b = static_cast<q4_20>(a);
        EXPECT_EQ(static_cast<float>(b), 2.0f);
    }
    {
        cdsp::virtual_float<q8_40> a{2.0f};
        cdsp::virtual_float<q4_20> b = static_cast<q4_20>(a);
        EXPECT_EQ(static_cast<float>(b), 2.0f);
    }

}

TEST(virtual_float, cumulative_sum_q4_20)
{
    std::mt19937 mt(91);
    std::uniform_real_distribution<float> fdist(-0.5, 0.5);
    double float_sum(0);
    cdsp::virtual_float<q4_20> vf_sum(0.0);
    for (unsigned int loop = 0; loop < 1000; loop++)
    {
        q4_20 efxp_num = static_cast<q4_20>(fdist(mt));
        double float_num = static_cast<double>(efxp_num);
        cdsp::virtual_float<q4_20> vfe_num = efxp_num;
        ASSERT_FLOAT_EQ(static_cast<float>(vfe_num), static_cast<float>(float_num));
        float_sum += float_num;
        vf_sum += vfe_num;
        EXPECT_NEAR(static_cast<float>(float_sum), static_cast<float>(vf_sum), 5e-4f);
    }
}

TEST(virtual_float, cumulative_sum_q8_40)
{
    std::mt19937 mt(91);
    std::uniform_real_distribution<float> fdist(-0.5, 0.5);
    double float_sum(0);
    cdsp::virtual_float<q8_40> vf_sum(0.0);
    for (unsigned int loop = 0; loop < 1000000; loop++)
    {
        q8_40 efxp_num = static_cast<q8_40>(fdist(mt));
        double float_num = static_cast<double>(efxp_num);
        cdsp::virtual_float<q8_40> vfe_num = efxp_num;
        ASSERT_FLOAT_EQ(static_cast<float>(vfe_num), static_cast<float>(float_num));
        float_sum += float_num;
        vf_sum += vfe_num;
        EXPECT_NEAR(static_cast<float>(float_sum), static_cast<float>(vf_sum), 1e-7f);
    }
}

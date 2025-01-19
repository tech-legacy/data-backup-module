/****************************************************************************
** MIT License
**
** Author	: xiaofeng.zhu
** Support	: zxffffffff@outlook.com, 1337328542@qq.com
**
****************************************************************************/
#include <gtest/gtest.h>
#include "Cryptography.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

TEST(Cryptography, Hash_SHA)
{
    std::string str = "XDFGHJafhdldknf@p9US*jknbgKSQ!~!@#$%^&*()_+}\"?><MNBVCXJHGV>NHBV-";

    for (int i = 0; i < 10; ++i)
    {
        constexpr size_t bits = 256;

        StringBuffer buf(str.data(), str.size());

        StringBuffer hash = Cryptography::Hash::SHA(buf, bits);
        StringBuffer hash2 = Cryptography::Hash::SHA(buf, bits);

        EXPECT_EQ(hash, hash2);
        EXPECT_NE(buf, hash);
        str += str;
    }
}

using System;
using Xunit;
using MAC.Types.User;

namespace MAC.Test.Types
{
    public class PasswordTests
    {
        [Fact]
        public void basic()
        {
            Password p = new Password("abc123!@#", false);
            Assert.True(p.Validate());
        }

        [Fact]
        public void verifyPassword()
        {
            Password p = new Password("abc123!@#", false);
            Assert.True(p.VerifyPassword("abc123!@#"));
        }

        [Fact]
        public void verifyPasswordFalse()
        {
            Password p = new Password("abc123!@#", false);
            Assert.False(p.VerifyPassword("abc123!@##"));
        }
    }
}

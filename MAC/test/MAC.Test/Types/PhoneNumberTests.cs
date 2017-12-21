using System;
using Xunit;
using MAC.Types.User;

namespace MAC.Test.Types
{
    public class PhoneNumberTests
    {
        [Fact]
        public void BasicUS()
        {
            PhoneNumber phone = new PhoneNumber("5152944111");
            Assert.True(phone.Validate());
        }

        [Fact]
        public void BasicUK()
        {
            PhoneNumber phone = new PhoneNumber("0800389886");
            Assert.True(phone.Validate());
        }

        [Fact]
        public void Equal()
        {
            PhoneNumber phone1 = new PhoneNumber("5152944111");
            PhoneNumber phone2 = new PhoneNumber("5152944111");
            Assert.True(phone1.Equals(phone2));
        }

        [Fact]
        public void NotEqual()
        {
            PhoneNumber phone1 = new PhoneNumber("5152944121");
            PhoneNumber phone2 = new PhoneNumber("5152944111");
            Assert.False(phone1.Equals(phone2));
        }
    }
}

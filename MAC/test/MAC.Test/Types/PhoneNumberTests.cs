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
            PhoneNumber phone = new PhoneNumber("5159862006");
            Assert.True(phone.Validate());
        }

        [Fact]
        public void BasicUK()
        {
            PhoneNumber phone = new PhoneNumber("0800389886");
            Assert.True(phone.Validate());
        }
    }
}

using System;
using Xunit;


namespace MAC.Test.Types
{
    public class StringTests
    {
        [Fact]
        public void BasicTest()
        {
            Assert.IsNotType(String, null);
        }

    }
}

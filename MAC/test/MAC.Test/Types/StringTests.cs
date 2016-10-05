using System;
using Xunit;
using MAC.Types;

namespace MAC.Tests.Types
{
    public class StringTests
    {
        [Fact]
        public void BasicTest()
        {
            MAC.Types.String s = new MAC.Types.String("apple");
            Assert.True(s.Validate());
        }

        [Fact]
        public void ToStringTest()
        {
            MAC.Types.String s = new MAC.Types.String("apple");
            Assert.Equal("apple", s.ToString());
        }

        public void CompareEqual()
        {
            MAC.Types.String s = new MAC.Types.String("apple");
            MAC.Types.String s2 = new MAC.Types.String("apple");
            Assert.Equal(0, s.CompareTo(s2));
        }

    }
}

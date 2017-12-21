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

        [Fact]
        public void CompareEqual()
        {
            MAC.Types.String s = new MAC.Types.String("apple");
            MAC.Types.String s2 = new MAC.Types.String("apple");
            Assert.Equal(0, s.CompareTo(s2));
        }

        [Fact]
        public void CompareNotEqual()
        {
            MAC.Types.String s = new MAC.Types.String("apple2");
            MAC.Types.String s2 = new MAC.Types.String("apple");
            Assert.Equal(1, s.CompareTo(s2));
        }

        [Fact]
        public void Equal()
        {
            MAC.Types.String s = new MAC.Types.String("apple");
            MAC.Types.String s2 = new MAC.Types.String("apple");
            Assert.True(s.Equals(s2));
        }

        [Fact]
        public void NotEqual()
        {
            MAC.Types.String s = new MAC.Types.String("apple2");
            MAC.Types.String s2 = new MAC.Types.String("apple");
            Assert.False(s.Equals(s2));
        }




    }
}

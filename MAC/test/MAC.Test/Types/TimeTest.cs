using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class TimeTest
    {
        [Fact]
        public void BasicTest()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Assert.True(time.Validate());
        }

        [Fact]
        public void EqualToSelf()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Assert.True(time.Equals(time));
        }

        [Fact]
        public void Equal()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Time time2 = new Time(new TimeSpan(20, 20, 20));
            Assert.True(time2.Equals(time));
        }

        [Fact]
        public void NotEqual()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Time time2 = new Time(new TimeSpan(20, 20, 10));
            Assert.False(time2.Equals(time));
        }

        [Fact]
        public void CompareToSelf()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Assert.Equal(0, time.CompareTo(time));
        }

        [Fact]
        public void CompareToSame()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Time time2 = new Time(new TimeSpan(20, 20, 20));
            Assert.Equal(0, time.CompareTo(time2));
        }
    }
}

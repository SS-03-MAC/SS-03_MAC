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
        public void CompareToSelf()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Assert.Equal(0, time.CompareTo(time));
        }
    }
}

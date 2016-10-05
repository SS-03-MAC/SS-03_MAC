using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class TimeTest
    {
        public void BasicTest()
        {
            Time time = new Time(new TimeSpan(20, 20, 20));
            Assert.True(time.Validate());
        }
    }
}

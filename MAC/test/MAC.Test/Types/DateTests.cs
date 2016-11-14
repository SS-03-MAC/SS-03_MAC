using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class DateTests
    {
        [Fact]
        public void basic()
        {
            Date d = new Date(new System.DateTime(2016, 11, 02));
            Assert.True(d.Validate());
        }

        [Fact]
        public void equalToSelf()
        {
            Date d = new Date(new System.DateTime(2016, 11, 02));
            Assert.True(d.Equals(d));
        }

        [Fact]
        public void eqaulToCopy()
        {
            Date d = new Date(new System.DateTime(2016, 11, 02));
            Date d2 = new Date(new System.DateTime(2016, 11, 02));
            Assert.True(d.Equals(d2));
        }

        [Fact]
        public void notEqual()
        {
            Date d = new Date(new System.DateTime(2016, 11, 02));
            Date d2 = new Date(new System.DateTime(2018, 11, 02));
            Assert.False(d.Equals(d2));
        }
    }
}

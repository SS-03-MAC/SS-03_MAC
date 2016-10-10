using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class BooleanTest
    {
        [Fact]
        public void basicTrue()
        {
            MAC.Types.Boolean b = new MAC.Types.Boolean(true);
            Assert.True(b.Validate());
        }

        [Fact]
        public void basicFalse()
        {
            MAC.Types.Boolean b = new MAC.Types.Boolean(true);
            Assert.True(b.Validate());
        }
    }
}

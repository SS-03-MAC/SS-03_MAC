using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class FloatTests
    {
        [Fact]
        public void Basic()
        {
            Float f = new Float(500);
            Assert.True(f.Validate());
        }
    }
}

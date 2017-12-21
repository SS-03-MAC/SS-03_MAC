using System;
using Xunit;
using MAC.Types;

namespace MAC.Test.Types
{
    public class CurrencyTests
    {
        [Fact]
        public void basicTets()
        {
            Currency C = new Currency(new decimal(50.00));
            Assert.True(C.Validate());
        }

        [Fact]
        public void LessThanACent()
        {
            Currency c = new Currency(new decimal(12.13337));
            Assert.True(c.Validate());
            Assert.Equal("12.13337", c.ToString());
        }

        [Fact]
        public void EqualToSelf()
        {
            Currency c = new Currency(new decimal(122222.15454));
            Assert.True(c.Equals(c));
        }

        [Fact]
        public void SameContrustor()
        {
            Currency c = new Currency(new decimal(122222.15454));
            Currency c2 = new Currency(new decimal(122222.15454));
            Assert.True(c.Equals(c2));
        }
    }
}

using System;
using Xunit;
using MAC.Types.User;

namespace MAC.Test.Types
{
    public class EmailTests
    {
        [Fact]
        public void basic()
        {
            Email e = new Email("mburket@iastate.edu");
            Assert.True(e.Validate());
        }

        [Fact]
        public void basicTypo()
        {
            Email e = new Email("mburket@iastate,edu");
            Assert.False(e.Validate());
        }

        [Fact]
        public void NoUser()
        {
            Email e = new Email("@iastate,edu");
            Assert.False(e.Validate());
        }

        [Fact]
        public void longTLDVaild()
        {
            Email e = new Email("matthew.burket@icloud.technology");
            Assert.True(e.Validate());
        }

        [Fact]
        public void eqaulToSelf()
        {
            Email e = new Email("mburket@iastate.edu");
            Assert.True(e.Equals(e));
        }
 
        [Fact]
        public void equalToCopyOfSelf()
        {
            Email e = new Email("mburket@iastate.edu");
            Email e2 = new Email("mburket@iastate.edu");
            Assert.True(e.Equals(e2));
        }
    }
}

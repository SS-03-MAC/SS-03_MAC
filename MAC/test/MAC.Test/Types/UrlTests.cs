using System;
using Xunit;
using MAC.Types.Internet;

namespace MAC.Test.Types
{
    public class UrlTests
    {
        [Fact]
        public void basic()
        {
            Url u = new Url(new Uri("https://google.com"));
            Assert.True(u.Validate());
        }
    }
}

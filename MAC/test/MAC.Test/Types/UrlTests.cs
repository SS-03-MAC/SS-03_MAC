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

        [Fact]
        public void equalSelf()
        {
            Url u = new Url(new Uri("https://google.com"));
            Assert.True(u.Equals(u));
        }

        [Fact]
        public void Equal()
        {
            Url u = new Url(new Uri("https://google.com"));
            Url u2 = new Url(new Uri("https://google.com"));
            Assert.True(u2.Equals(u));
        }

        [Fact]
        public void NotEqual()
        {
            Url u = new Url(new Uri("http://google.com"));
            Url u2 = new Url(new Uri("https://google.com"));
            Assert.False(u2.Equals(u));
        }

        [Fact]
        public void CompareEqual()
        {
            Url u = new Url(new Uri("https://google.com"));
            Url u2 = new Url(new Uri("https://google.com"));
            Assert.Equal(0, u.CompareTo(u2));
        }

        [Fact]
        public void CompareNotEqual()
        {
            Url u = new Url(new Uri("https://google.com"));
            Url u2 = new Url(new Uri("http://google.com"));
            Assert.Equal(1, u.CompareTo(u2));
        }
    }
}

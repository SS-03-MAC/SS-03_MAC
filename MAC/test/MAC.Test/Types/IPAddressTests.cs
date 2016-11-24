using System;
using Xunit;
using MAC.Types.Internet;

namespace MAC.Tests.Types
{
    public class IPAddressTests
    {
        [Fact]
        public void BasicTest()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("69.89.31.226", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.Equal(wrapper.Value, test);
        }

        [Fact]
        public void IsIPv6Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("2002:4559:1FE2::4559:1FE2", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.True(wrapper.IsIPv6());
        }

        [Fact]
        public void IsNotIPv4Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("2002:4559:1FE2::4559:1FE2", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.False(wrapper.IsIPv4());
        }

        [Fact]
        public void IsNotIPv6Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("129.168.31.223", out test);
            IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.False(wrapper.IsIPv6());
        }

        [Fact]
        public void IsIPv4Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("69.89.31.226", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.True(wrapper.IsIPv4());
        }
    }
}
﻿using System;
using Xunit;
using MAC.Types.Internet;

namespace MAC.Tests.Types
{
    public class IPAddressTests
    {
        public void BasicTest()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("69.89.31.226", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.Equal(wrapper.Value, test);
        }

        public void IsIPv6Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("2002:4559:1FE2::4559:1FE2", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.True(wrapper.IsIPv6());
        }

        public void IsIPv4Test()
        {
            System.Net.IPAddress test;
            System.Net.IPAddress.TryParse("69.89.31.226", out test);
            MAC.Types.Internet.IPAddress wrapper = new MAC.Types.Internet.IPAddress(test);
            Assert.True(wrapper.IsIPv4());
        }
    }
}
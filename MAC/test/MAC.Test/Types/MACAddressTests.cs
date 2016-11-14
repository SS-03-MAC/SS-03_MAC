using System;
using Xunit;
using MAC.Types.Internet;

namespace MAC.Test.Types.Internet
{
    public class MACAddressTests
    {
        [Fact]
        public void ValidateTest()
        {
            MAC.Types.Internet.MACAddress valid1 =
                new MAC.Types.Internet.MACAddress("012.345.678.9AB");
            MAC.Types.Internet.MACAddress valid2 =
                new MAC.Types.Internet.MACAddress("CD-EF-ab-cd-ef-01");
            MAC.Types.Internet.MACAddress valid3 =
                new MAC.Types.Internet.MACAddress("ab:cd:ef:AB:CD:EF");
            MAC.Types.Internet.MACAddress invalid1 =
                new MAC.Types.Internet.MACAddress("apple");
            MAC.Types.Internet.MACAddress invalid2 =
                new MAC.Types.Internet.MACAddress("01-23-45:678.9AB");
            MAC.Types.Internet.MACAddress invalid3 =
                new MAC.Types.Internet.MACAddress("0123456789AB");

            Assert.True(valid1.Validate());
            Assert.True(valid2.Validate());
            Assert.True(valid3.Validate());
            Assert.False(invalid1.Validate());
            Assert.False(invalid2.Validate());
            Assert.False(invalid3.Validate());
        }

        [Fact]
        public void CompareToTest()
        {
            MAC.Types.Internet.MACAddress address1 =
                new MAC.Types.Internet.MACAddress("012.345.678.9AB");
            MAC.Types.Internet.MACAddress address2 =
                new MAC.Types.Internet.MACAddress("01:23:45:67:89:AB");
            MAC.Types.Internet.MACAddress address3 =
                new MAC.Types.Internet.MACAddress("F12.345.678.9AB");

            Assert.True(address1.CompareTo(address2) == 0);
            Assert.True(address1.CompareTo(address3) < 0);
        }

        [Fact]
        public void EqualsTest()
        {
            MAC.Types.Internet.MACAddress address1 =
                new MAC.Types.Internet.MACAddress("012.345.678.9AB");
            MAC.Types.Internet.MACAddress address2 =
                new MAC.Types.Internet.MACAddress("01:23:45:67:89:AB");

            Assert.True(address1.Equals(address2));
        }

        [Fact]
        public void NotEqualsTest()
        {
            MAC.Types.Internet.MACAddress address1 =
                new MAC.Types.Internet.MACAddress("012.345.678.9AA");
            MAC.Types.Internet.MACAddress address2 =
                new MAC.Types.Internet.MACAddress("01:23:45:67:89:AB");

            Assert.False(address1.Equals(address2));
        }
    }
}

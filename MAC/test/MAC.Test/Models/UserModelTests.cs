using System;
using System.Data.SqlClient;
using Xunit;
using MAC.Models;

namespace MAC.Test.Models
{
    public class UserModelTests
    {
        [Fact]
        public void DeleteNoSave()
        {
            User u = new User();
            Assert.Throws<InvalidOperationException>(() => u.Delete());
        }

        [Fact]
        public void Save()
        {
            User u = new User { FullName = new MAC.Types.String("Matthew"), City = new MAC.Types.String("Ames"), Email = new MAC.Types.User.Email("matthew@assignitapp.com"), PasswordDigest = new MAC.Types.User.Password("apple", false) };
            Assert.True(u.Save());
        }

    }
}

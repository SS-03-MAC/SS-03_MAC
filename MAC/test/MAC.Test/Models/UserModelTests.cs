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

        [Fact]
        public void Update()
        {
            string email = "matthew" + DateTime.Now.Ticks + "@assignitapp.com";
            User u = new User { FullName = new MAC.Types.String("Matthew"), City = new MAC.Types.String("Ames"), Email = new MAC.Types.User.Email(email), PasswordDigest = new MAC.Types.User.Password("apple", false) };
            u.Save();
            u.FullName = new MAC.Types.String("Joel");
            Assert.True(u.Save());
        }

        [Fact]
        public void Delete()
        {
            string email = "matthew" + DateTime.Now.Ticks + "@assignitapp.com";
            User u = new User { FullName = new MAC.Types.String("Matthew"), City = new MAC.Types.String("Ames"), Email = new MAC.Types.User.Email(email), PasswordDigest = new MAC.Types.User.Password("apple", false) };
            u.Save();
            Assert.True(u.Delete());
        }

    }
}

using System;
using Xunit;
using MAC.Models;
using System.Data.SqlClient;
using System.Collections.Generic;

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

        [Fact]
        public void GetAll()
        {
            SqlDataReader q = Query.RunQuery("SELECT Id from users");
            int rows = 0;
            while (q.Read())
            {
                rows++;
            }
            List<User> users = User.Get();
            Assert.Equal(rows, users.Count);
        }

        [Fact]
        public void GetOneNotFound()
        {
            Assert.Throws<RecordNotFoundException>(() => User.Get(133777333));
        }

        [Fact]
        public void GetOneFound()
        {
            string email = "matthew" + DateTime.Now.Ticks + "GetOne@assignitapp.com";
            User u = new User { FullName = new MAC.Types.String("Matthew"), City = new MAC.Types.String("Ames"), Email = new MAC.Types.User.Email(email), PasswordDigest = new MAC.Types.User.Password("apple", false) };
            u.Save();
            User u2 = User.Get(u.Id.Value);
            //Assert.Equal(u, u2);
        }
    }
}

using System;
using System.Data.SqlClient;
using Xunit;
using MAC.Models;

namespace MAC.Test.Models
{
    public class BaseModelFactoryTest
    {
        [Fact]
        public void basicTest()
        {
            using (SqlConnection conn = new SqlConnection("Server=localhost;Database=MACDevlopment;Integrated Security=true"))
            {
                conn.Open();
                using (SqlCommand cmd = new SqlCommand())
                {
                    cmd.Connection = conn;
                    cmd.CommandText = "INSERT INTO [dbo].[Users] ([PasswordDigest] ,[FullName] ,[City] ,[Email] ,[CreatedAt] ,[UpdatedAt]) VALUES ('$2a$10$6RcfaGmYSb.TY7EV0ZiZM..M.Yn2W2JBuRzotG9koNUQQKWPp/rwm' ,'Matthew Burket' ,'Ames' ,'mburket@iastate.edu' ,'2016-10-24 23:59:59.990' ,'2016-10-24 23:59:59.990')";
                    cmd.ExecuteNonQuery();
                }
                using (SqlCommand cmd = new SqlCommand())
                {
                    cmd.Connection = conn;
                    cmd.CommandText = "SELECT * FROM Users where Email = 'mburket@iastate.edu'";
                    using (SqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            User user = (User)BaseModelFactory.FillModel(typeof(MAC.Models.User), reader);
                            User expectedUser = new User
                            {
                                FullName = new MAC.Types.String("Matthew Burket"),
                                PasswordDigest = new MAC.Types.User.Password("$2a$10$6RcfaGmYSb.TY7EV0ZiZM..M.Yn2W2JBuRzotG9koNUQQKWPp/rwm"),
                                City = new MAC.Types.String("Ames"),
                                Email = new MAC.Types.User.Email("mburket@iastate.edu"),
                                CreatedAt = new MAC.Types.DateTime(DateTime.Parse("2016-10-24 23:59:59.990")),
                                UpdatedAt = new MAC.Types.DateTime(DateTime.Parse("2016-10-24 23:59:59.990"))
                        
                            };
                            Assert.True(expectedUser.Equals(expectedUser));
                        }
                    }
                }
            }
        }
    }
}

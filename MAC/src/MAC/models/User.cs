using MAC.Models.Attributes;
using MAC.Types;
using MAC.Types.User;

namespace MAC.Models
{
    [TableName("Users")]
    public partial class User : BaseModel<User>
    {
        /// <summary>
        /// A basic string field
        /// </summary>
        /// <returns></returns>
        [Required]
        [DatabaseField("Email")]
        public Email Email { get; set; }


        [Required]
        [DatabaseField("FullName")]
        public String FullName { get; set; }

        /// <summary>
        /// On set will set PasswordDigest to the BCrypt Password
        /// </summary>
        [Required]
        [Length(Minimum = 10, Maximum = 72)]
        public virtual string Password { get; set; }
        /// <summary>
        /// How the Password is stored in the database
        /// </summary>
        /// <returns></returns>
        [DatabaseField("PasswordDigest")]
        public Password PasswordDigest { get; set; }

        /// <summary>
        /// City 
        /// </summary>
        [DatabaseField("City")]
        public String City { get; set; }
    }
}

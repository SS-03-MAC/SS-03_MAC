using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;
using MAC.Types;
using MAC.Types.User;

namespace MAC.Models
{
    [TableName("Users")]
    [UrlName("users")]
    public partial class User : BaseModel<User>
    {
        /// <summary>
        /// A basic string field
        /// </summary>
        /// <returns></returns>
        [RequiredField]
        [DatabaseField("Email")]
        public Email Email { get; set; }


        [RequiredField]
        [DatabaseField("FullName")]
        public String FullName { get; set; }

        /// <summary>
        /// On set will set PasswordDigest to the BCrypt Password
        /// </summary>
        [MaxLength(Maximum = 72, AllowBlank = true)]
        [MinLength()]
        public string LengthChecker { get; set; }
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

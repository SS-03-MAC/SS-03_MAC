using System;
using MAC.Types;
using MAC.Types.User;
using MAC.Types.Internet;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;

namespace MAC.Models
{
    [TableName("auths")]
    [UrlName("auths")]
    public partial class Auth : BaseModel<Auth>
    {



        [DatabaseField("token")]
        public MAC.Types.String Token { get; set; }




        [DatabaseField("OnwerId")]
        public Integer OnwerId { get; set; }


        public override bool Save()
        {
            return base.Save();
        }

    }

}

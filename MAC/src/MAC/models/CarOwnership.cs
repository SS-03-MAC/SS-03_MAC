using MAC.Models;
using MAC.Models.Attributes;
using MAC.Models.Attributes.Validations;
using MAC.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.models
{
    [TableName("CarOwnership")]
    [UrlName("CarOwnerships")]
    public class CarOwnership : BaseModel<CarOwnership>
    {
        [RequiredField]
        [DatabaseField("UserId")]
        public Integer UserId { get; set; }

        [RequiredField]
        [DatabaseField("CarId")]
        public Integer CarId { get; set; }

        public virtual User User
        {
            get
            {
                return User.Get(UserId.Value);
            }
            set
            {
                UserId = value.Id;
            }
        }

        public virtual Car Car
        {
            get
            {
                return Car.Get(CarId.Value);
            }

            set
            {
                CarId = value.Id;
            }
        }
    }
}

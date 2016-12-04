using MAC.Models;
using MAC.Types;
using MAC.Models.Attributes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.models
{
    [TableName("Car")]
    [UrlName("cars")]
    public class Car : BaseModel<Car>
    {
        [DatabaseField("Make")]
        public Types.String Make { get; set; }

        [DatabaseField("Make")]
        public Types.String Model { get; set; }
    }
}

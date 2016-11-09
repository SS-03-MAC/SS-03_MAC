using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models
{
    interface IBaseModel
    {
        bool Save();
        bool Validate();
    }
}

using System;

namespace MAC.Models.Attributes
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
    public class TableName : Attribute
    {
        /// <summary>
        /// Name of table
        /// </summary>
        /// <example>
        /// For example if User model and the data was stored in the ysers table
        /// you would do the following:
        /// <code>
        ///     [TableName("Users")]
        ///     public class User : BaseModel<Users> {
        ///         // Model Code here
        ///     }
        /// </code>
        /// </example>
        public string Name { get; }

        /// <summary>
        /// Create Attribute with a name
        /// </summary>
        /// <param name="Name">Name of table</param>
        public TableName(string Name)
        {
            this.Name = Name;
        }
    }
}

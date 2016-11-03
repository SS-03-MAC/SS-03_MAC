using System;

namespace MAC.Models.Attributes
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
    public class TableName : Attribute
    {
        /// <summary>
        /// Name of table
        /// </summary>
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

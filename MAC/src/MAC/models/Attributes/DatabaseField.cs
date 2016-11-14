using System;

namespace MAC.Models.Attributes
{
    /// <summary>
    /// Tells MAC where the field is stored in the database
    /// </summary>
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, AllowMultiple = false)]
    public class DatabaseField : Attribute
    {
        /// <summary>
        /// Name of the Database field
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// Create attribute with a name
        /// </summary>
        /// <param name="name">Name of database field</param>
        public DatabaseField(string name)
        {
            Name = name;
        }
    }
}

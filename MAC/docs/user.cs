using System;
using System.Collections;

/// <summary>
///   Screensketch: Matthew Burket
///   This is an example model class.
///   I have subbed out the methods that will created in this file by the automatic system.
/// </summary>
public class User {
  /// <summary>
  Database id
  /// </summary>
  public long Id {get;}
  /// <summary>
  /// A basic string field
  /// </summary>
  /// <returns></returns>
  public string Email {get; set;}
  /// <summary>
  /// On set will set PasswordDigest to the BCrypt Password
  /// </summary>
  public virtual strng Password {get; set;}
  /// <summary>
  /// How the Password is stored in the database
  /// </summary>
  /// <returns></returns>
  public string PasswordDigest {get; set;}
  /// <summary>
  /// Built-in field
  /// </summary>
  /// <returns></returns>
  public DateTime CreatedAt {get; set;}
  /// <summary>
  /// Built-in field
  /// </summary>
  /// <returns></returns>
  public DateTime CreatedAt
  public DateTime UpdatedAt {get; set;}


  /// <summary>
  ///  Get a user given a Id
  /// </summary>
  /// <param name="id"></param>
  /// <returns>Users</returns>
  public static User Get(long id) {
    // SELECT
  }

  public static List<Users> GetAll() {
    // SELECT
  }

  public bool Save() {
    if (Id == null) {
      // INSERT
      // Validate
      // If Valid will update Id on model
    } else {
      // Valid
      // UPDATE
    }
  }

  public bool Delete() {
    // DELETE
  }

  public bool Valid() {
    // Runs Validations
    // Returns if all vaildtions passed
  }

  public List<string> GetValidationsErrors() {
    // Gets Validation Errors
  }
}

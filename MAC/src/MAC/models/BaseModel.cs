public abstract class BaseModel {
  private string TableName;

  public long Id { get; }

  public BaseModel() {

  }

  public abstract bool Save();

  public abstract bool Update();
}

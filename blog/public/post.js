var Post = function(Title, Body, PublishedAt){
  this.Title = Title;
  this.Body = Body;
  this.PublishedAt = PublishedAt;
  this.Id = 0;
  this.CreatedAt = Date.now();
  this.UpdatedAt = Date.now();

  this.save = function(path, successHandler, failureHandler){
    var xhr = new XMLHttpRequest();
    if(this.Id == 0){
      xhr.open("POST", path + "/posts/", true);
    } else{
      xhr.open("PATCH", path + "/posts/"+this.Id);
    }

    xhr.setRequestHeader("Content-type", "application/json");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          if(successHandler !== undefined) {
            successHandler(xhr);
          }
        } else{
          if(failureHandler !== undefined) {
            failureHandler(xhr);
          }
        }
      }
    };

    var data = JSON.stringify(this);
    xhr.send(data);
  };

  this.delete = function(path, successHandler, failureHandler){
    if(this.Id == 0){
      return; //never saved to database, don't have to do anything
    }

    var xhr = new XMLHttpRequest();
    xhr.open("DELETE", path + "/posts/"+this.Id, true);
    xhr.setRequestHeader("Content-type", "application/json");
    xhr.onreadystatechange = function() {
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          if(successHandler !== undefined) {
            successHandler(xhr);
          }
        } else{
          if(failureHandler !== undefined) {
            failureHandler(xhr);
          }
        }
      }
    };

    xhr.send(null);
  };

  
  
  
};

Post.get = function(id, ret, path, successHandler, failureHandler){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Title", "Body", "PublishedAt"];
        var result = JSON.parse(xhr.responseText);

        for(var field in result){
          if(fields.indexOf(field) !== -1){
            if(obj[field].Value !== undefined) {
              ret[field] = obj[field].Value;
            } else {
              ret[field] = result[field];
            }
          }
        }

        if(successHandler !== undefined){
          successHandler(xhr);
        }
      } else{
        if (failureHandler !== undefined) {
          failureHandler(xhr);
        }
      }
    }
  };

  xhr.open("GET", path + "/posts/"+id, true);
  xhr.send(null);
};

Post.getAll = function(arr, path){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Title", "Body", "PublishedAt"];
        var result = JSON.parse(xhr.responseText);

        for(var i = 0; i < result.length; i++){
          tmp = new Post();
          obj = result[i];
          for(var field in obj){
            if(fields.indexOf(field) !== -1){
              if (obj[field].Value !== undefined) {
                tmp[field] = obj[field].Value;
              }
              else {
                tmp[field] = obj[field];
              }
            }
          }

          arr.push(tmp);
        }

        if(successHandler !== undefined) {
          successHandler(xhr);
        }
      } else{
        if(failureHandler !== undefined) {
          failureHandler(xhr);
        }
      }
    }
  };

  xhr.open("GET", path + "/posts", true);
  xhr.send(null);
};

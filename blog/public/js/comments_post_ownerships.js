var CommentsPostOwnerships = function(post, comments){
  this.PostId = post;
  this.CommentsId = comments;
  this.Id = 0;
  this.CreatedAt = Date.now();
  this.UpdatedAt = Date.now();

  this.save = function(path, successHandler, failureHandler){
    var ret = this
    var xhr = new XMLHttpRequest();
    if(this.Id == 0){
      xhr.open("POST", path + "/comments_post_ownerships/", true);
    } else{
      xhr.open("PATCH", path + "/comments_post_ownerships/"+this.Id);
    }

    xhr.setRequestHeader("Content-type", "application/json");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          var result = JSON.parse(xhr.responseText);
          if(result.Id !== undefined){
            ret.Id = result.Id;
          }

          if(successHandler !== undefined) {
            successHandler(xhr, ret, result);
          }
        } else{
          if(failureHandler !== undefined) {
            failureHandler(xhr, ret, result);
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
    xhr.open("DELETE", path + "/comments_post_ownerships/"+this.Id, true);
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

  
  this.getPost = function(path, successHandler, failureHandler){
    var ret = new Post();
    Post.get(this.PostId, ret, path, successHandler, failureHandler);
    return ret;
  };
  
  
  this.getComments = function(path, successHandler, failureHandler){
    var ret = new Comments();
    Comments.get(this.CommentsId, ret, path, successHandler, failureHandler);
    return ret;
  };
  
};

CommentsPostOwnerships.get = function(id, ret, path, successHandler, failureHandler){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["Id", "CreatedAt", "UpdatedAt", "PostId", "CommentsId"];
        var result = JSON.parse(xhr.responseText);

        for(var field in result){
          if(fields.indexOf(field) !== -1){
            if(result[field].Value !== undefined) {
              ret[field] = result[field].Value;
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

  xhr.open("GET", path + "/comments_post_ownerships/"+id, true);
  xhr.send(null);
};

CommentsPostOwnerships.getAll = function(arr, path, successHandler, failureHandler){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["Id", "CreatedAt", "UpdatedAt", "PostId", "CommentsId"];
        var result = JSON.parse(xhr.responseText);

        for(var i = 0; i < result.length; i++){
          tmp = new CommentsPostOwnerships();
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

  xhr.open("GET", path + "/comments_post_ownerships", true);
  xhr.send(null);
};

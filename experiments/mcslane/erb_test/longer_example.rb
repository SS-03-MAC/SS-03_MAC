require 'erb'

def get_courses()
  ['Abstract Algebra', 'Stats', 'Algorithms', 'Com S 309']
end

def get_template()
  %{
    Course Schedule for <%= @date.strftime('%A') %>

    You are taking:

      <% for @course in @courses %>
        <%= @course %>
      <% end %>
  }
end

class CourseSchedule
  attr_accessor :courses, :template, :date

  def initialize(courses, template, date=Time.now)
    @date = date
    @courses = courses
    @template = template
  end

  def render
    ERB.new(@template).result(binding)
  end

  def save(file)
    File.open(file, 'w+') do |f|
      f.write(render)
    end
  end
end

schedule = CourseSchedule.new(get_courses, get_template)
schedule.save('./Files/schedule.txt')
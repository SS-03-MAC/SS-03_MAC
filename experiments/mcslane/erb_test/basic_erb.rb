require 'erb'

weekday = Time.now.strftime('%A')
simple_template = "Today is <%= weekday %>"

render = ERB.new(simple_template)
puts output = render.result()

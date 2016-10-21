require 'erb'
require 'obstruct'

# This class allows us to do ERB generation using a Hash. We do this by 
# wrapping the hash as an OpenStruct, then calling either method to generate
# the erb file.

# Given a Hash h and a Template t, we can generate the file from ERB in either
# of the following ways:
# HashGenerator.new(h).render(t)
# HashGenerator.render_from_hash(t, h)
module Generation
  class HashGenerator < OpenStruct
    def render(template)
      ERB.new(template).result(binding)
    end

    def self.render_from_hash(template, in_hash)
      HashGenerator.new(in_hash).render(template)
    end 
  end
end
defmodule EigenTest do
  use ExUnit.Case
  doctest Eigen

  test "greets the world" do
    assert Eigen.hello() == :world
  end
end

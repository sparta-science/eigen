defmodule Eigen.NIFsTest do
  use ExUnit.Case, async: true

  test "matrix3d_test" do
    assert Eigen.NIFs.matrix3d_test() == [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]]
  end

  test "add" do
    assert Eigen.NIFs.add(1, 3) == 4
    assert Eigen.NIFs.add(4, 1) == 5
  end
end

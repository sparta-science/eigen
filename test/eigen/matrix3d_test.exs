defmodule Matrix3dTest do
  use ExUnit.Case, async: true

  alias Eigen.Matrix3d

  describe "new" do
    test "initializes a struct with a pointer to C memory" do
      matrix3d = Matrix3d.new()
      assert %Matrix3d{__reference__: reference} = matrix3d
      assert reference |> is_reference()
    end
  end

  describe "to_list" do
    test "uses a reference to create a list of lists" do
      matrix3d = Matrix3d.new()

      assert matrix3d |> Matrix3d.to_list() == [
               [1.0, 2.0, 3.0],
               [4.0, 5.0, 6.0],
               [7.0, 8.0, 9.0]
             ]
    end
  end
end

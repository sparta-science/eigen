defmodule Eigen.Matrix3d do
  alias Eigen.NIFs

  defstruct ~w{
    __resource__
  }a

  def new() do
    resource = NIFs.matrix3d_new()
    %__MODULE__{__resource__: resource}
  end

  def to_list(%__MODULE__{} = matrix) do
    NIFs.matrix3d_to_list(matrix.__resource__)
  end
end

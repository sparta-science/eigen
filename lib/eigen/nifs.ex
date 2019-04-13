defmodule Eigen.NIFs do
  @moduledoc false

  @on_load :load_nifs

  @doc false
  @spec load_nifs :: :ok
  def load_nifs do
    priv_dir =
      case :code.priv_dir(__MODULE__) do
        {:error, _error} ->
          :code.which(__MODULE__)
          |> :filename.dirname()
          |> :filename.dirname()
          |> Path.join("priv")

        path ->
          path
      end

    case :erlang.load_nif(Path.expand(:filename.join(priv_dir, "eigen")), 0) do
      :ok ->
        :ok

      {:error, {:load_failed, reason}} ->
        IO.warn("Error loading NIF #{reason}")
        :ok
    end
  end

  def matrix3d_new(), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_random(), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_test(), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_to_list(_resource), do: :erlang.nif_error(:nif_library_not_loaded)
  def add(first, second) when is_integer(first) and is_integer(second), do: :erlang.nif_error(:nif_library_not_loaded)
end

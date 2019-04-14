defmodule Eigen.Nif do
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

    case :erlang.load_nif(Path.expand(:filename.join(priv_dir, "eigen_nif")), 0) do
      :ok ->
        :ok

      {:error, {:load_failed, reason}} ->
        IO.warn("Error loading NIF #{reason}")
        :ok
    end
  end

  def matrix3d_empty(), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_new(_list), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_to_list(ref) when is_reference(ref), do: :erlang.nif_error(:nif_library_not_loaded)

  def matrix3d_add(augend_ref, addend_ref)
      when is_reference(augend_ref) and is_reference(addend_ref),
      do: :erlang.nif_error(:nif_library_not_loaded)

  def matrix3d_div_scalar(ref, _divisor) when is_reference(ref),
    do: :erlang.nif_error(:nif_library_not_loaded)

  def matrix3d_mult_scalar(ref, _multiplier) when is_reference(ref),
    do: :erlang.nif_error(:nif_library_not_loaded)
end

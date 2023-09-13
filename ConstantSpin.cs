using UnityEngine;

public class ConstantSpin : MonoBehaviour
{
    public float rotationSpeed = 10f;

    private void Update()
    {
        // Rotate the object around its up vector with the specified speed
        transform.Rotate(Vector3.forward, rotationSpeed * Time.deltaTime);
    }
}


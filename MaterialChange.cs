using UnityEngine;

public class MaterialChange : MonoBehaviour
{
    public Material initialMaterial;
    public Material finalMaterial;
    public float delayTime = 6f; // The delay time before the transition starts in seconds
    public float transitionTime = 5f; // The time it takes for the transition to complete in seconds

    private  Renderer objectRenderer;
    private float currentTime = 0f;
    private bool transitionStarted = false;

    void Start()
    {
        objectRenderer = GetComponent<Renderer>();
        objectRenderer.material = initialMaterial;
    }

    void Update()
    {
        if (!transitionStarted)
        {
            currentTime += Time.deltaTime;

            if (currentTime >= delayTime)
            {
                transitionStarted = true;
                currentTime = 0f;
            }
        }
        else
        {
            currentTime += Time.deltaTime;
            float t = Mathf.Clamp01(currentTime / transitionTime); // Normalize time between 0 and 1

            // Interpolate material properties between the initial and final materials
            objectRenderer.material.Lerp(initialMaterial, finalMaterial, t);

            if (currentTime >= transitionTime)
            {
                // Transition completed, do any necessary cleanup or additional actions
                // For example, you might want to disable the script or change the object's behavior.
                enabled = false;
            }
        }
    }
}

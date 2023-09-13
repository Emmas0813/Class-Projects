using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneSwitcher : MonoBehaviour
{
    string scene;
    public void LoadScene()
    {
       
        SceneManager.LoadScene("Oil_refinery");
    }
}


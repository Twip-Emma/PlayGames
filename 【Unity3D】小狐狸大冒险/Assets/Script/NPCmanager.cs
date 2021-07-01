using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class NPCmanager : MonoBehaviour
{

    public GameObject dialogImage;//对话

    public GameObject tipImage;

    public float showTime = 4;//对话框显示时间
    private float showTimer;//对话框显示计时器
    // Start is called before the first frame update
    void Start()
    {
        tipImage.SetActive(true);
        dialogImage.SetActive(false);
        showTimer = -1;
    }

    // Update is called once per frame
    void Update()
    {
        showTimer -=Time.deltaTime;
        if(showTimer < 0){
            tipImage.SetActive(true);
            dialogImage.SetActive(false);
        }
    }

    public void ShowDialog(){
        showTimer = showTime;
        tipImage.SetActive(false);
        dialogImage.SetActive(true);
    }
}
